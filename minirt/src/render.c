/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:21:01 by aouardao          #+#    #+#             */
/*   Updated: 2023/08/27 18:13:18 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void print(t_vec3 a)
{
	printf("%f\t%f\t%f\n", a.x, a.y , a.z);
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

uint32_t to_color(uint8_t a,t_vec3 vec)
{
	return (((uint32_t)vec.x << 24 ) | ((uint32_t)vec.y << 16 ) | ((uint32_t)vec.z << 8) | a);
}


void render_scene(t_scene  *scene,mlx_image_t *img)
{
    scene->cam = ft_cam(scene);
	ft_drew(scene, img);
}
