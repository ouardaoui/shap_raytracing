/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drew.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:12:19 by aouardao          #+#    #+#             */
/*   Updated: 2023/08/27 19:15:55 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_point	ft_get_color(t_scene *scene, t_cam cam, float i, float j)
{
	t_vec3	dir;
	t_vec3	ori;
	t_point	data;

	ori = cam.pos;
	dir = vec3_sub(color_scale(i, cam.hor), color_scale(-j, cam.ver));
	dir = vec3_add(dir, cam.c);
	dir = vec3_norm(vec3_sub(dir, ori));
	data = intersect_objects(scene, ori, dir);
	return (data);
}

t_point	handle_shadow(t_vec3 pts, t_vec3 n, t_light *li, t_scene *scene)
{
	t_vec3	ori;
	t_vec3	dir;

	ori = vec3_add(pts, color_scale(0.0001, n));
	dir = vec3_norm(vec3_sub(li->pos, ori));
	return (intersect_objects(scene, ori, dir));
}

t_vec3	c_comp(t_light *light, t_point shadow, t_vec3 hit_point)
{
	t_vec3	light_normal;
	float	gain;
	float	r2;
	float	light_bright;
	t_vec3	shadow_color;

	light_normal = vec3_sub(light->pos, hit_point);
	r2 = vec2_dot(light_normal, light_normal);
	gain = vec2_dot(vec3_norm(light_normal), shadow.normal);
	if (gain <= 0)
		light_bright = 0;
	else
		light_bright = (light->ratio * gain * 1000) / (4.0 * 3.1415 * r2);
	shadow_color = color_scale(light_bright, shadow.color);
	return (vec3_dot(shadow_color, light->color));
}

uint32_t	ft_color_shadow(t_scene *scene, t_point data, mlx_image_t *img,
		t_vec3 normal)
{
	t_vec3		am;
	t_vec3		c;
	t_light		*li;
	uint32_t	color;

	color = 0;
	li = scene->object.li_lst;
	am = scene->amb.color;
	c = vec3_dot(data.color, am);
	while (li)
	{
		if (handle_shadow(data.hit_point, normal, li, scene).intersect == false)
		{
			c = vec3_add(c, c_comp(li, data, data.hit_point));
			c = ft_limit(c);
		}
		color = to_color(255, color_scale(255, c));
		li = li->next;
	}
	return (color);
}

void	ft_drew(t_scene *scene, mlx_image_t *img)
{
	int			i;
	int			j;
	t_point		data;
	t_vec3		normal;
	uint32_t	color;

	j = -1;
	while (++j < HEIGHT)
	{
		i = -1;
		while (++i < WIDTH)
		{
			data = ft_get_color(scene, scene->cam, (float)i / WIDTH, \
					(float)j / HEIGHT);
			if (data.intersect == true)
			{
				normal = ft_handle_normal(&data);
				color = ft_color_shadow(scene, data, img, normal);
				mlx_put_pixel(img, i, HEIGHT - 1 - j, color);
			}
			else
				mlx_put_pixel(img, i, HEIGHT - 1 - j, 0xff000000);
		}
	}
}
