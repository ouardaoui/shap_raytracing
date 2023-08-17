/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 03:45:01 by aouardao          #+#    #+#             */
/*   Updated: 2023/08/17 03:45:41 by aouardao         ###   ########.fr       */
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
	return ((t_vec3){alpha * a.x, alpha * a.y, alpha * a.z});
}