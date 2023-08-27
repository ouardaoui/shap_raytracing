/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:15:37 by aouardao          #+#    #+#             */
/*   Updated: 2023/08/27 17:16:22 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_vec3 ft_normal_plane(t_point *data)
{
				t_vec3 normal;
				(*data).hit_point = get_hit_point(*data);
				if(vec2_dot((*data).dir, (*data).normal) > 0)
				(*data).normal = color_scale(-1, (*data).normal);
				normal = (*data).normal; 
				return normal;
}
t_vec3 ft_normal_sphere(t_point *data)
{
			t_vec3  normal;
				(*data).hit_point = get_hit_point(*data);
				normal = vec3_sub((*data).hit_point,(*data).normal); 
				(*data).normal = vec3_norm(normal);
				return normal;
}
t_vec3 ft_normal_cylindre(t_point *data)
{
			t_vec3 normal;
			(*data).hit_point = get_hit_point(*data);
			normal = (*data).normal;
			normal = vec3_norm(normal); 

			return normal;
}

t_vec3 ft_handle_normal(t_point *data)
{
	t_vec3 normal;

	if((*data).type == plane)
			normal = ft_normal_plane(data);	
	if((*data).type == sphere)	
			normal = ft_normal_sphere(data);
	if((*data).type == cylinder)
			normal = ft_normal_cylindre(data);	
	return normal;
}