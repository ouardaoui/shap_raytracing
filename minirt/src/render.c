/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:21:01 by aouardao          #+#    #+#             */
/*   Updated: 2023/08/27 20:18:19 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_cam	ft_cam(t_scene *scene)
{
	t_cam	cam;
	t_unitv	uv;
	float	vp[2];
	float	f;

	cam = scene->cam;
	f = (float)cam.fov * 11 / (float)1260;
	vp[0] = 2 * tan(f);
	vp[1] = vp[0] * (float)HEIGHT / (float)WIDTH;
	uv.w = vec3_norm(color_scale(-1, cam.dir));
	uv.u = vec3_cross((t_vec3){0, 1, 0}, uv.w);
	uv.v = vec3_cross(uv.w, uv.u);
	cam.hor = color_scale(vp[0], uv.u);
	cam.ver = color_scale(vp[1], uv.v);
	cam.c = vec3_sub(cam.pos, color_scale(0.5, cam.hor));
	cam.c = vec3_sub(cam.c, color_scale(0.5, cam.ver));
	cam.c = vec3_sub(cam.c, uv.w);
	return (cam);
}

double	intersect_sphere(t_sphere *sphere, t_vec3 ray_origin, t_vec3 ray_dir)
{
	t_equa	vs;
	double	t1;
	double	t2;

	vs.o = vec3_sub(ray_origin, sphere->center);
	vs.a = vec2_dot(ray_dir, ray_dir);
	vs.b = 2.0 * vec2_dot(vs.o, ray_dir);
	vs.c = vec2_dot(vs.o, vs.o) - sphere->radius * sphere->radius;
	vs.h = vs.b * vs.b - 4 * vs.a * vs.c;
	if (vs.h < 0)
		return (-1.0);
	else
	{
		t1 = (-vs.b + sqrt(vs.h)) / (2.0 * vs.a);
		t2 = (-vs.b - sqrt(vs.h)) / (2.0 * vs.a);
		return (fmin(t1, t2));
	}
}

double	intersect_plane(t_plane *plane, t_vec3 ray_origin, t_vec3 ray_dir)
{
	t_vec3	nor;
	double	denominator;
	t_vec3	point_to_plane;
	double	t;

	nor = vec3_norm(plane->normal);
	denominator = vec2_dot(nor, ray_dir);
	if (fabs(denominator) > 1e-6)
	{
		point_to_plane = vec3_sub(plane->point, ray_origin);
		t = vec2_dot(point_to_plane, plane->normal) / denominator;
		if (t >= 0)
		{
			return (t);
		}
	}
	return (-1.0);
}

uint32_t	to_color(uint8_t a, t_vec3 vec)
{
	return (((uint32_t)vec.x << 24) | ((uint32_t)vec.y << 16) | \
	((uint32_t)vec.z << 8) | a);
}

void	render_scene(t_scene *scene, mlx_image_t *img)
{
	scene->cam = ft_cam(scene);
	ft_drew(scene, img);
}
