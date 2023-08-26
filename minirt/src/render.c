#include "../include/minirt.h"


void print(t_vec3 a)
{
	printf("%f\t%f\t%f\n", a.x, a.y , a.z);
}

t_vec3		vec3_cross(t_vec3 v, t_vec3 u)
{
    t_vec3 vec;
    
    vec.x = (v.y * u.z) - (v.z * u.y);
    vec.y = (v.z * u.x) - (v.x * u.z);
    vec.z = (v.x * u.y) - (v.y * u.x); 
    
    return vec;
}

double vec3_length(t_vec3 vec)
{
    return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

double vec3_dis(t_vec3 vec, t_vec3 a)
{
    return sqrt(vec.x * a.x + vec.y * a.y + vec.z * a.z);
}

t_vec3	vec3_add(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3 result;
    
	result.x = vec1.x + vec2.x;
	result.y = vec1.y + vec2.y;
	result.z = vec1.z + vec2.z;
	return (result);
}

double	vec2_dot(t_vec3 vec1, t_vec3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_vec3	vec3_dot(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3 vec;

	vec.x = vec1.x * vec2.x;
	vec.y = vec1.y * vec2.y;
	vec.z = vec1.z * vec2.z;

	return vec;
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


	float f = (float)cam.fov * 22 / (float)1260;
	vp[0] = 2 * tan((float)f / 2);
	vp[1] = vp[0] * (float)HEIGHT  / WIDTH;
	w = vec3_norm(color_scale(-1,cam.dir));
	u = vec3_cross((t_vec3){0, 1, 0}, w);
	v = vec3_cross(w, u);
	cam.hor = color_scale(vp[0],u);
	cam.ver = color_scale(vp[1],v);
	cam.c = vec3_sub(cam.pos, color_scale(0.5 ,cam.hor));
	cam.c = vec3_sub(cam.c, color_scale(0.5 , cam.ver));
	cam.c = vec3_sub(cam.c, w); //lower view corner;
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
        return (-1.0); 
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

double intersect_plane(t_plane *plane, t_vec3 ray_origin, t_vec3 ray_dir) {
	t_vec3 nor = vec3_norm(plane->normal);
    double denominator = vec2_dot(nor, ray_dir);
    if (fabs(denominator) > 1e-6) {
        t_vec3 point_to_plane = vec3_sub(plane->point, ray_origin);
        double t = vec2_dot(point_to_plane, plane->normal) / denominator;
        if (t >= 0) {
            return t;
        }
    }
    return -1.0; // No intersection
}

double intersect_cylindre(t_cylinder *cy, t_vec3 ray_origin, t_vec3 ray_dir, int *v)
{
	t_vec3 normal = vec3_norm(cy->axis);
	
	t_vec3 pos = ray_origin;
	t_vec3 d = ray_dir;
	float t[2];
	float dis[2];
	bool bol[2];

	t_vec3 dir = handle_coor(d, normal);
    t_vec3 o = vec3_sub(pos, cy->center); 
	t_vec3 oc = handle_coor(o, normal);
    double a = vec2_dot(dir, dir); 
    double b = 2.0 * vec2_dot(oc, dir); 
    double c = vec2_dot(oc, oc) - (cy->diameter * cy->diameter); 
    double discriminant = b * b - 4 * a * c; 
    if (discriminant < 0)
        return -1; 
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
		{
			*v = 1;
			return t[1];
		}
		return -1;

    }
}

uint32_t to_color(uint8_t a,t_vec3 vec)
{
	return (((uint32_t)vec.x << 24 ) | ((uint32_t)vec.y << 16 ) | ((uint32_t)vec.z << 8) | a);
}

t_point set_data(double t , double s_t, int type, t_vec3 vec)
{
	t_point data;

	data.t = t;
	data.s_t = -1;
	data.intersect = true;
	data.type = type;
	data.color = vec;
	return data;
}

t_point intersect_objects(t_scene *scene, t_vec3 ray_origin, t_vec3 ray_dir)
{
	double t;
	t_vec3 vec;
	int back_side;
	t_point data;

	back_side = 0;
	uint32_t color;
    t_sphere *current_sphere = scene->object.sp_lst;
	t_cylinder *current_cylindre = scene->object.cy_lst;
	t_plane *current_plane = scene->object.pl_lst;
	data = set_data(-1,-1, NONE, (t_vec3){0.0,0.0,0.0});
	data.t = MAX_T;
	data.intersect = false;
    while (current_sphere != NULL)
    {
	    t = intersect_sphere(current_sphere, ray_origin, ray_dir);
        if (t >= 0.000001 && t < data.t)
		{
			vec = current_sphere->color;
			data = set_data(t,-1,sphere,vec);
			data.dir = (t_vec3){ray_dir.x,ray_dir.y,ray_dir.z};
			data.ori = (t_vec3){ray_origin.x, ray_origin.y,ray_origin.z};
			data.normal = current_sphere->center;
		}
        current_sphere = current_sphere->next;
    }
	/*
	while (current_cylindre != NULL)
    {
        t = intersect_cylindre(current_cylindre, ray_origin, ray_dir,&back_side);
        if (t > 0 &&  t < data.t)
		{
			vec = current_cylindre->color;
			data = set_data(t,-1,cylinder, vec);
			data.normal = vec3_norm(current_cylindre->axis);
			if(back_side)
			{
				data = set_data(-1, t ,cylinder ,vec);
				data.normal = color_scale(-1,current_cylindre->axis);
			}
			data.dir = (t_vec3){ray_dir.x,ray_dir.y,ray_dir.z};
			data.ori = (t_vec3){ray_origin.x, ray_origin.y,ray_origin.z};
		}
        current_cylindre = current_cylindre->next;
    }
	*/
	while (current_plane != NULL)
    {
        t = intersect_plane(current_plane, ray_origin, ray_dir);
        if (t > 0 && t < data.t)
		{
			vec = current_plane->color;
			data = set_data(t, 0, plane , vec);
			data.dir = (t_vec3){ray_dir.x,ray_dir.y,ray_dir.z};
			data.normal = vec3_norm(current_plane->normal);
			data.ori = (t_vec3){ray_origin.x, ray_origin.y,ray_origin.z};
		}
        current_plane = current_plane->next;
		
    }
	return data;
}

t_point ft_get_color(t_scene *scene,t_cam cam , float i, float j)
{
	t_vec3 dir;
	t_vec3 ori;
	t_point data;

	ori = cam.pos;
	dir = vec3_sub(color_scale(i,cam.hor), color_scale(-j,cam.ver));
	dir = (t_vec3){dir.x + cam.c.x , dir.y + cam.c.y , dir.z + cam.c.z};
	dir = vec3_norm(vec3_sub(dir, ori));
	data = intersect_objects(scene, ori,dir);
	return data;
}


t_vec3 get_hit_point(t_point data)
{
	t_vec3 vec;

	vec = color_scale(data.t, data.dir);
	vec.x = vec.x + data.ori.x;
	vec.y = vec.y + data.ori.y;
	vec.z = vec.z + data.ori.z;
	return vec;
}

t_point handle_shadow(t_vec3 pts, t_vec3 n, t_light *li,t_scene *scene)
{
	t_vec3 ori = vec3_add(pts,color_scale(0.0001, n));
	t_vec3 dir = vec3_norm(vec3_sub(li->pos,ori));
	return(intersect_objects(scene,ori,dir));
}

t_vec3			c_comp(t_light *light, t_point shadow, t_vec3 hit_point)
{
	t_vec3		light_normal;
	float		gain;
	float		r2;
	float		light_bright;
	t_vec3 shadow_color;
	int light_color;

	light_normal = vec3_sub(light->pos, hit_point);
	r2 = vec2_dot(light_normal,light_normal);
	gain = vec2_dot(vec3_norm(light_normal), shadow.normal);
	if (gain <= 0)
		light_bright = 0;
	else
		light_bright = (light->ratio * gain * 1000) / 
						(4.0 * 3.1415 * r2);
	//shadow_color = to_color(0,color_scale(255,shadow.color));
	//light_color = to_color(0,color_scale(255,light->color));	
	shadow_color = color_scale(light_bright, shadow.color);	
	return vec3_dot(shadow_color,light->color);
	//return (c_prod(c_add(0, c_scale(shadow_color, light_bright)), light_color));
}

double limitation(double n)
{
	if(n > 1)
		return 1;
	if(n < 0)
		return 0;
	return n;
}

t_vec3 ft_limit(t_vec3 vec)
{
	t_vec3 c;
	c.x = limitation(vec.x);
	c.y = limitation(vec.y);
	c.z = limitation(vec.z);

	return c;
}

void ft_drew(t_scene *scene, mlx_image_t *img)
{
	int i;
	int j;
	t_point data;
	t_point shadow;
	t_vec3 hit_point;
	t_vec3 normal;
	t_light *li;
	uint32_t color;
	t_vec3 am;
	t_vec3 c;

	color = 0;
	li = scene->object.li_lst;
	j = 0; 	
	while(j < HEIGHT) 
	{
		i = 0;
		while(i < WIDTH)
		{
			data= ft_get_color(scene,scene->cam, (float)i / WIDTH , (float)j / HEIGHT); 
			if(data.intersect == true  && data.type == plane)
			{
				hit_point = get_hit_point(data);
				if(vec2_dot(data.dir, data.normal) > 0)
					data.normal = color_scale(-1, data.normal);
				normal = data.normal; 
			}
			if(data.intersect == true && data.type == sphere)
			{
				hit_point = get_hit_point(data);
				normal = vec3_sub(hit_point,data.normal); // data.ormal is center of shpere
				data.normal = vec3_norm(normal);
			}
			if(data.intersect == true)
			{
				am =  scene->amb.color;
				c = vec3_dot(data.color, am);

				t_light *tmp = li;
				if(tmp)
				{
					shadow = handle_shadow(hit_point,normal,tmp,scene);
					if(shadow.intersect == false)
					{
						c = vec3_add(c,c_comp(tmp,data, hit_point));
						c = ft_limit(c);
					}
					color = to_color(255,color_scale(255,c));
					tmp = tmp->next;
				}
				/*
				t_vec3 normal = vec3_norm(hit_point);
				normal = vec3_norm(normal);
			    t_vec3  light = scene->object.li_lst->pos ;
				light = vec3_norm(light);
				float d = fmax(0.0,vec2_dot(normal ,light));
				c = color_scale(d,c);
				color = to_color(255,color_scale(255,c));
				*/
				mlx_put_pixel(img, i,HEIGHT - 1 - j,color);
			}
			else 
				mlx_put_pixel(img, i,HEIGHT - 1 - j,0xff000000);
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