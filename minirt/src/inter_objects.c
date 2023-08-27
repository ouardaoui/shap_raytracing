/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:19:11 by aouardao          #+#    #+#             */
/*   Updated: 2023/08/27 17:20:09 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"


t_point init_data(void)
{
	t_point data;

	data.t = MAX_T;
	data.s_t = -1;
	data.type = NONE;
	data.	color = set_vec(0.0,0.0,0.0);
	data.intersect = false;
	return data;
}
void loop_sphere(t_scene *scene,t_point *data, t_vec3 ray_origin, t_vec3 ray_dir)
{
	double t;
  t_sphere *current_sphere ;

	current_sphere = scene->object.sp_lst;
	while (current_sphere != NULL)
    {
	    t = intersect_sphere(current_sphere, ray_origin, ray_dir);
        if (t >= 0.0001 && t < (*data).t)
		{
			*data = set_data(t,-1,sphere,current_sphere->color);
			(*data).dir =  color_scale(1, ray_dir);
			(*data).ori = color_scale(1,ray_origin); 
			(*data).normal = current_sphere->center;
		}
        current_sphere = current_sphere->next;
    }
}
void loop_cylindre(t_scene *scene, t_point *data, t_vec3 ray_origin, t_vec3 ray_dir)
{
	double t;
	t_cylinder *current_cylindre ;
	t_vec3 normal;
	int back_side;

	normal = set_vec(0.0 , 0.0 , 0.0);
	back_side = 0;
	current_cylindre = scene->object.cy_lst;
	while (current_cylindre != NULL)
    {
        t = intersect_cylindre(current_cylindre, ray_origin, ray_dir,&back_side);
        if (t > 0 &&  t <(*data).t)
		{
			(*data) = set_data(t,-1,cylinder, current_cylindre->color);
			(*data).dir = color_scale(1, ray_dir); 
			(*data).ori = color_scale(1,ray_origin); 
			normal = color_scale(t, current_cylindre->axis);
			normal = vec3_add(normal, current_cylindre->center);
			normal =  vec3_sub(get_hit_point(*data), normal);
			if(back_side)
				(*data).normal = color_scale(-1,normal);
			(*data).normal = normal;
		}
        current_cylindre = current_cylindre->next;
    }
}
void loop_plane(t_scene *scene, t_point *data, t_vec3 ray_origin, t_vec3 ray_dir)
{	
	double t;
	t_plane *current_plane ;

	current_plane = scene->object.pl_lst;
	while (current_plane != NULL)
    {
        t = intersect_plane(current_plane, ray_origin, ray_dir);
        if (t > 0 && t < (*data).t)
		{
			(*data) = set_data(t, 0, plane , current_plane->color);
			(*data).dir = color_scale(1, ray_dir);
			(*data).ori = color_scale(1,ray_origin); 
			(*data).normal = vec3_norm(current_plane->normal);
		}
        current_plane = current_plane->next;	
    }
}

t_point intersect_objects(t_scene *scene, t_vec3 ray_origin, t_vec3 ray_dir)
{
	double t;
	t_vec3 vec;
	t_point data;
	
	data = init_data();	   
	loop_sphere(scene,&data, ray_origin,ray_dir);
	loop_cylindre(scene,&data, ray_origin, ray_dir);
	loop_plane(scene,&data,ray_origin,ray_dir );	
	return data;
}