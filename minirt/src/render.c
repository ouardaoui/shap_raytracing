
#include "../include/minirt.h"

t_vec3		vec3_cross(t_vec3 v, t_vec3 u)
{
    t_vec3 vec;
    
    vec.x = (v.y * u.z) - (v.z * u.y);
    vec.y = (v.z * u.x) - (v.x * u.z);
    vec.z = (v.x * u.y) - (v.y * u.x); 
    
    return vec;
}

double	vec2_dot(t_vec3 vec1, t_vec3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_vec3 handle_coor(t_vec3 a, t_vec3 n)
{
	t_vec3 res;
	double cos = vec2_dot(a,n);
	t_vec3 nn = (t_vec3){n.x * cos , n.y * cos, n.z * cos};
	res = vec3_sub(a,nn);

	return res;
}


t_cam ft_cam(t_scene *scene)
{
    t_cam cam = scene->cam;

    float	vp[2];
	t_vec3	w;
	t_vec3	u;
	t_vec3	v;

	vp[0] = 2 * tan((float)cam.fov / 2);
	vp[1] = vp[0] * (float)HEIGHT  / WIDTH;
	w = vec3_norm(color_scale(-1,cam.dir));
	u = vec3_cross((t_vec3){0, 1, 0}, w);
	v = vec3_cross(w, u);
	cam.hor = color_scale(vp[0],u);
	cam.ver = color_scale(vp[1],v);
	cam.c = vec3_sub(cam.pos, color_scale(0.5 ,cam.hor));
	cam.c = vec3_sub(cam.c, color_scale(0.5 , cam.ver));
	cam.c = vec3_sub(cam.c, w); //lower view corner
    return cam;
}

double intersect_sphere(t_sphere *sphere, t_vec3 ray_origin, t_vec3 ray_dir)
{
    t_vec3 oc = vec3_sub(ray_origin, sphere->center);
    double a = vec2_dot(ray_dir, ray_dir);
    double b = 2.0 * vec2_dot(oc, ray_dir);
    double c = vec2_dot(oc, oc) - sphere->radius * sphere->radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return (-1.0); // No intersection
    else
    {
        double t1 = (-b + sqrt(discriminant)) / (2.0 * a);
        double t2 = (-b - sqrt(discriminant)) / (2.0 * a);
        return fmin(t1, t2);
    }
}

float ft_dis(t_vec3 pos,t_vec3 oc, float t,t_vec3 normal,t_vec3 d)
{
		d = (t_vec3){d.x * t ,d.y * t, d.z *t};
		oc = (t_vec3){oc.x * -1 ,oc.y * -1, oc.z *-1};
		float k = vec2_dot(normal,vec3_sub(d, oc));

		return k;
}

double intersect_cylindre(t_cylinder *cy, t_vec3 ray_origin, t_vec3 ray_dir)
{
	t_vec3 normal = vec3_norm(cy->axis);
	
	t_vec3 pos = ray_origin;
	t_vec3 d = ray_dir;
	float t[2];
	float dis[2];
	bool bol[2];

	t_vec3 dir = handle_coor(d, normal);
    t_vec3 o = vec3_sub(pos, cy->center); // (0 , 0, 5)
	t_vec3 oc = handle_coor(o, normal);
    double a = vec2_dot(dir, dir); // 1;
    double b = 2.0 * vec2_dot(oc, dir); //[0 , -10]
    double c = vec2_dot(oc, oc) - (cy->diameter * cy->diameter); //[0 ,25]
    double discriminant = b * b - 4 * a * c; 

	//printf("%f\n", discriminant);
    if (discriminant < 0)
        return -1; // No intersection
    else
    {
		
        double t0 = (-b + sqrt(discriminant)) / (2.0 * a);
        double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
        t[0] =  fmin(t0, t1);
		t[1] = fmax(t0, t1);

		dis[0] = ft_dis(pos,o, t[0], normal, d);
		dis[1] = ft_dis(pos,o, t[1], normal, d);
		bol[0] = dis[0] >= 0 && dis[0] <= cy->height && t[0] > 0.0;
		bol[1] = dis[1] >= 0 && dis[1] <= cy->height && t[1] > 0.0;
		if(bol[0])
			return t[0];
		if(bol[0] == false &  bol[1] == true)
			return t[1];
		return -1;
    }
}

double intersect_objects(t_scene *scene, t_vec3 ray_origin, t_vec3 ray_dir)
{
    double closest_t = -1.0;
	double t;

    t_sphere *current_sphere = scene->object.sp_lst;
	t_cylinder *current_cylindre = scene->object.cy_lst;
    while (current_sphere != NULL)
    {
        t = intersect_sphere(current_sphere, ray_origin, ray_dir);
        if (t > 0 && (closest_t < 0 || t < closest_t))
            closest_t = t;
        current_sphere = current_sphere->next;
    }
	while (current_cylindre != NULL)
    {
        t = intersect_cylindre(current_cylindre, ray_origin, ray_dir);
        if (t > 0 && (closest_t < 0 || t < closest_t))
            closest_t = t;
        current_cylindre = current_cylindre->next;
    }
    return (closest_t);
}

uint32_t ft_get_color(t_scene *scene,t_cam cam , float i, float j)
{
	t_vec3 dir;
	t_vec3 ori;
	
	ori = cam.pos;
	dir = vec3_sub(color_scale(i,cam.hor), color_scale(-j,cam.ver));
	dir = (t_vec3){dir.x + cam.c.x , dir.y + cam.c.y , dir.z + cam.c.z};
	dir = vec3_norm(vec3_sub(dir, ori));

	double t = intersect_objects(scene, ori,dir);

	if(t < 0)
		return 0xff000000;
	return 0xffffffff;
}



void ft_drew(t_scene *scene, mlx_image_t *img)
{
	int i;
	int j;
	uint32_t color;

	j = 0; 
	while(j < HEIGHT - 1) 
	{
		i = 0;
		while(i < WIDTH - 1)
		{
			color = ft_get_color(scene,scene->cam, (float)i / WIDTH , (float)j / HEIGHT); 
			mlx_put_pixel(img, i, j, color);
			i++;
		}
		j++;
	}
}

void render_scene(t_scene  *scene,mlx_image_t *img)
{
    scene->cam = ft_cam(scene);
	ft_drew(scene, img);
}