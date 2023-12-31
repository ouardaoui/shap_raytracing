
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include "MLX42.h"
#define WIDTH 1200
#define HEIGHT 800

typedef struct {
    float x;
	float y;
	float z;
} Vector;

typedef struct {
    float r;
	float g;
	float b;
	float a;
} f_Vector;


typedef struct {
	uint8_t r , g , b, a;		
} Vector_4;

typedef struct {
    Vector center;
    float radius;
} Sphere;

Vector vec2_norm(Vector a)
{
	Vector b;
    double length = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    double alpha = 1.0 / length;

	b.x  = ((a.x * alpha) + 1) * 0.5;
	b.y  = ((a.y * alpha) + 1) * 0.5;
	b.z  = ((a.z * alpha) + 1) * 0.5;
    return (b);
}

Vector normalize(Vector a)
{
	Vector b;
    double length = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    double alpha = 1.0 / length;

	b.x  = a.x * alpha;
	b.y  = a.y * alpha;
	b.z  = a.z * alpha;
    return (b);
}


Vector_4 vec4_norm(Vector_4 a)
{
	Vector_4 b;
    double length = sqrt(a.b * a.b + a.r * a.r + a.g * a.g + a.a * a.a);
    double alpha = 0.0 / length;

	b.b  = a.b * alpha;
	b.r  = a.r * alpha;
	b.g  = a.g * alpha;
	b.r	 = b.r * alpha;
    return (b);
}

Vector_4 to_vec(uint32_t color)
{
	Vector_4 a;
	a.a = (uint8_t)color;
	a.b = (uint8_t)(color >> 8);
	a.g = (uint8_t)(color >> 16);
	a.r = (uint8_t)(color >> 24);

	return (a);
}

uint32_t to_color(Vector_4 vec)
{
	return (((uint32_t)vec.r << 24 ) | ((uint32_t)vec.g << 16 ) | ((uint32_t)vec.b << 8) | (uint32_t)vec.a);
}

static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

double	vec2_dot(Vector vec1, Vector vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

 Vector	vec2_sub(Vector a, Vector b)
{
	return ((Vector){a.x - b.x, a.y - b.y, a.z - b.z});
}

Vector distance(Vector pos, Vector dir, double t)
{
	Vector d;

	d.x = pos.x + dir.x * t;
	d.y = pos.y + dir.y * t;
	d.z = pos.z + dir.z * t;

	return d;
}

f_Vector ft_color(float x,float y)
{

	Vector dir = {x, y, -1};
    //dir = vec2_norm(dir);
	Sphere sp = {{5,5,0}, 2};
	Vector pos = {0,0,12};
	Vector light = {0,6,0}; 

    Vector oc = vec2_sub(pos, sp.center); // (0 , 0, 5)
    double a = vec2_dot(dir, dir); // 1;
    double b = 2.0 * vec2_dot(oc, dir); //[0 , -10]
    double c = vec2_dot(oc, oc) - (sp.radius * sp.radius); //[0 ,25]
    double discriminant = b * b - 4 * a * c; 

    if (discriminant < 0)
        return ((f_Vector){1,1.0,1.0,1.0}); // No intersection
    else
    {
        double t1 = (-b + sqrt(discriminant)) / (2.0 * a);
        double t0 = (-b - sqrt(discriminant)) / (2.0 * a);
        double t =  fmin(t1, t0);
		Vector m = distance(pos, dir , t);
		m = normalize(m);

		light = normalize(light);
		//light = (Vector){-light.x, -light.y, -light.z};
		double d = fmax(vec2_dot(m ,light), 0.0); // cos(angle)
		f_Vector color = (f_Vector){1 * d, 1 *d, 1 	*d , 1};
		//f_Vector mm = {color.x , color.y  ,color.z ,-1};
		return ((f_Vector){color.r , color.g, color.b, color.a});
    }

}
void ft_hook(void *parms)
{
	mlx_t *mlx = (mlx_t *)parms;

	if(mlx_is_key_down(mlx, MLX_KEY_CAPS_LOCK))
		mlx_close_window(mlx);	
}

void render(mlx_image_t *img)
{
	int i = 0;
	int j = 0;
	f_Vector color;
	
	while(j < 800)
	{
		i = 0;
		while(i < 1200)
		{
		
			float x = i  / (float)1200; // 0 - 400 , 800 - 400  
            float y = j /  (float)799;
			//x = 2.0 * x - 1;						
			//y = 2.0 * y - 1;
			printf("%f\t%f\n", x, y);
			color = ft_color(x, y)	;
			mlx_put_pixel(img, i, 800 - j, to_color((Vector_4){color.r * 255, color.g * 255, color.b *255, 255}));
			i++;
		}
 		j++;
	}
}

int main()
{
    mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "41Balls", false);
	if (!mlx)
		ft_error();


	mlx_image_t* img = mlx_new_image(mlx, 1200, 800);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();
	render(img);
	mlx_loop_hook(mlx,ft_hook ,mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
