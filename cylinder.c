
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include "MLX42.h"
#define WIDTH 800
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
	float h;
} Cylinder;

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

Vector vec_norm(Vector a)
{
	Vector b;
    double length = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    double alpha = 1.0 / length;

	b.x = a.x * alpha;
	b.y = a.y * alpha;
	b.z = a.z * alpha;

	return b;
}

Vector vec_sub(Vector u, Vector v)
{
	return ((Vector){u.x - v.x , u.y - v.y , u.z - v.z});
}


Vector vec_dot(Vector u, Vector v)
{
	return ((Vector){u.x * v.x , u.y * v.y , u.z * v.z });
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

Vector handle_coor(Vector a, Vector n)
{
	Vector res;
	double cos = vec2_dot(a,n);
	Vector nn = (Vector){n.x * cos , n.y * cos, n.z * cos};
	res = vec2_sub(a,nn);

	return res;
}

float ft_dis(Vector pos, float t,Vector normal,Vector d)
{
		Vector s = (Vector){pos.x + t * d.x ,pos.y + t * d.y ,pos.z + t * d.z };
		s = vec_sub(s, vec_sub(s,vec_dot(normal ,s))); 
		float r =sqrt(s.x * s.x + s.y * s.y  + s.z * s.z);
		return r;
}

f_Vector ft_color(float x,float y)
{

	Vector d = {x , y, -1} ;
	Vector normal = {5,1,5};
	normal = vec_norm(normal);
    //dir = vec2_norm(dir);
	Cylinder cy = {{0,0,0}, 2, 10};
	Vector pos = {0,0, 10};
	Vector light = {0,1 ,1}; // in fact light is (-1,-1,-1)
	float t[2];
	float dis[2];
	bool bol[2];

	//Vector dir = vec_sub(d,vec_dot(normal, d));
	Vector dir = handle_coor(d, normal);
    Vector o = vec2_sub(pos, cy.center); // (0 , 0, 5)
	Vector oc = handle_coor(o, normal);
    double a = vec2_dot(dir, dir); // 1;
    double b = 2.0 * vec2_dot(oc, dir); //[0 , -10]
    double c = vec2_dot(oc, oc) - (cy.radius * cy.radius); //[0 ,25]
    double discriminant = b * b - 4 * a * c; 

	//printf("%f\n", discriminant);
    if (discriminant < 0)
        return ((f_Vector){0,0,0,1}); // No intersection
    else
    {
		
        double t0 = (-b + sqrt(discriminant)) / (2.0 * a);
        double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
        t[0] =  fmin(t0, t1);
		t[1] = fmax(t0, t1);

		dis[0] = ft_dis(pos, t[0], normal, d);
		dis[1] = ft_dis(pos, t[1], normal, d);
		bol[0] = (dis[0] >= cy.center.y - (cy.h * 0.5)) && (dis[0] <= cy.center.y + (cy.h * 0.5)) && t[0] > 0.0;
		bol[1] = (dis[1] >= cy.center.y - (cy.h * 0.5)) && (dis[1] <= cy.center.y + (cy.h * 0.5)) && t[1] > 0.0;
		//bol[0] = (dis[0] >= cy.center.y)  && (dis[0] <= cy.center.y + cy.h ) && t[0] > 0.0;
		//bol[0] = (dis[0] >= cy.center.y) && (dis[0] <= cy.center.y + cy.h ) && t[0] > 0.0;
		if(bol[0])
			return((f_Vector){1,1,1,1});
		if(bol[0] == false &  bol[1] == true)
			return((f_Vector){1,1,1,1});	
		return((f_Vector){0,0,0,1});
		/*Vector m = distance(pos, dir , t);
		m = vec2_norm(m);
		light = vec2_norm(light);
		double d = fmax(vec2_dot(m ,light), 0.0); // cos(angle)
		Vector color = vec2_norm((Vector){1*(float)d , (float)0.0 , 1*(float)d});
		//printf("%f\t%f\t%f\n", color.x, color.y, color.z);
		f_Vector mm = {color.x , color.y  ,color.z ,0};
		return ((f_Vector){m.x, m.y , m.z,0});
		*/
        //return 0xfffffffe;
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
		while(i < 800)
		{
			float x = (1.0 - 2.0 * (i + 0.5) / 799);
            float y = (1.0 - 2.0 * (j + 0.5) / 799) ;						
			color = ft_color(x, y);
			//printf("%f\t%f\t%f\n", color.b, color.g, color.r);
			mlx_put_pixel(img, i, j, to_color((Vector_4){255 * color.r, 255 *color.g , 255 *color.b , 255 * color.r}));
			i++;
		}
 		j++;
	}
}

int main()
{
    mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "41Balls", true);
	if (!mlx)
		ft_error();


	mlx_image_t* img = mlx_new_image(mlx, 799, 800);
	if (!img || (mlx_image_to_window(mlx, img, -1, 0) < 0))
		ft_error();

	render(img);

	mlx_loop_hook(mlx,ft_hook ,mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}