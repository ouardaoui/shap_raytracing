/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:23:48 by aouardao          #+#    #+#             */
/*   Updated: 2023/08/27 17:35:09 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

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
t_vec3 get_hit_point(t_point data)
{
	t_vec3 vec;

	vec = color_scale(data.t, data.dir);
	vec.x = vec.x + data.ori.x;
	vec.y = vec.y + data.ori.y;
	vec.z = vec.z + data.ori.z;
	return vec;
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