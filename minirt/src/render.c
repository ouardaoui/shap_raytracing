/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:21:01 by aouardao          #+#    #+#             */
/*   Updated: 2023/08/27 17:34:58 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minirt.h"

void print(t_vec3 a)
{
	printf("%f\t%f\t%f\n", a.x, a.y , a.z);
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

	float f = (float)cam.fov * 11 / (float)1260;
	vp[0] = 2 * tan(f);
	vp[1] = vp[0] * (float)HEIGHT  / (float)WIDTH;
	w = vec3_norm(color_scale(-1,cam.dir));
	u = vec3_cross((t_vec3){0, 1, 0}, w);
	v = vec3_cross(w, u);
	cam.hor = color_scale(vp[0],u);
	cam.ver = color_scale(vp[1],v);
	cam.c = vec3_sub(cam.pos, color_scale(0.5 ,cam.hor));
	cam.c = vec3_sub(cam.c, color_scale(0.5, cam.ver));
	cam.c = vec3_sub(cam.c, w); 
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


void render_scene(t_scene  *scene,mlx_image_t *img)
{
    scene->cam = ft_cam(scene);
	ft_drew(scene, img);
}
