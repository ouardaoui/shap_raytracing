/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 03:41:26 by aouardao          #+#    #+#             */
/*   Updated: 2023/08/17 06:59:16 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	parse_cam(t_scene *scene, char **split)
{
	t_vec3	look_at;
	
	if (scene->cam.set)
		dprintf(2, "Parsing Error in Camera\n");
	if (ft_array_len(split) != 4)
		dprintf(2, "Invalid Number of args in param %s: ", split[0]);
	parse_vec3(split[1], &(scene->cam.pos));
	scene->cam.pos_initial = scene->cam.pos;
	parse_vec3(split[2], &look_at);
	scene->cam.dir = vec3_norm(vec3_sub(look_at, scene->cam.pos));
	scene->cam.dir_initial = scene->cam.dir;
	stoi(split[3], 1, 179, &(scene->cam.fov));
	scene->cam.set = true;
}

void	parse_amb(t_scene *scene, char **split)
{
	if (ft_array_len(split) != 3)
		dprintf(2, "Invalid Number of args in param : %s\n", split[0]);
	stod(split[1], &(scene->amb.brightness));
	parse_color(split[2], &(scene->amb.color));
	scene->amb.color = color_scale(scene->amb.brightness, scene->amb.color);
	scene->amb.set = true;
}
void	parse_light(t_scene *scene, char **split)
{
	if (ft_array_len(split) != 4)
		dprintf(2, "Invalid Number of args in param %s: ", split[0]);
  t_light *new_light = create_light_node();
	parse_vec3(split[1], &(new_light->pos));
	stod(split[2], &(new_light->ratio));
	parse_color(split[3], &(new_light->color));
	scene->light.color = color_scale(scene->light.ratio, scene->light.color);
	scene->light.set = true;
  add_light_to_back(&(scene->object.li_lst), new_light);
}
void	parse_sphere(t_scene *scene, char **split)
{
	if (ft_array_len(split) != 4)
		dprintf(2, "Invalid Number of args in param %s: ", split[0]);
	t_sphere *new_sphere = create_sphere_node();
	parse_vec3(split[1], &(new_sphere->center));
	stod(split[2], &(new_sphere->radius));
	parse_color(split[3], &(new_sphere->color));
	new_sphere->radius = new_sphere->radius / 2.0;
	new_sphere->set = true;
	add_sphere_to_back(&(scene->object.sp_lst), new_sphere);
}

void	parse_plane(t_scene *scene, char **split)
{
	if (ft_array_len(split) != 4)
		dprintf(2, "Invalid Number of args in param %s: ", split[0]);
  t_plane *new_plane = create_plane_node();
	parse_vec3(split[1], &(new_plane->point));
	parse_vec3(split[2], &(new_plane->normal));
	parse_color(split[3], &(new_plane->color));
	scene->plane.set = true;
  	add_plane_to_back(&(scene->object.pl_lst), new_plane);
}
void	parse_cylinder(t_scene *scene, char **split)
{
	if (ft_array_len(split) != 6)
		dprintf(2, "Invalid Number of args in param %s: ", split[0]);
  t_cylinder *new_cylinder = create_cylinder_node();
	parse_vec3(split[1], &(new_cylinder->center));
	parse_vec3(split[2], &(new_cylinder->axis));
	stod(split[3], &(new_cylinder->diameter));
	new_cylinder->diameter /= 2;
	stod(split[4], &(new_cylinder->height));
	parse_color(split[5], &(new_cylinder->color));
	scene->cylinder.set = true;
  	add_cylinder_to_back(&(scene->object.cy_lst), new_cylinder);
}