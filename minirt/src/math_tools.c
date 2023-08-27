/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 03:45:01 by aouardao          #+#    #+#             */
/*   Updated: 2023/08/27 17:11:20 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vec3	vec3_norm(t_vec3 a)
{
	double	alpha;

	alpha = 1.0 / sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	return (color_scale(alpha, a));
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
    return (sqrt(vec.x * a.x + vec.y * a.y + vec.z * a.z));
}