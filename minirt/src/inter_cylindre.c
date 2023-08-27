/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cylindre.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:42:34 by aouardao          #+#    #+#             */
/*   Updated: 2023/08/27 20:46:33 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

float	ft_dis(t_vec3 pos, t_vec3 oc, t_vec3 normal, t_vec3 d)
{
	float	k;

	oc = color_scale(-1, oc);
	k = vec2_dot(normal, vec3_sub(d, oc));
	return (k);
}

t_vec3	handle_coor(t_vec3 a, t_vec3 n)
{
	t_vec3	res;
	double	cos;
	t_vec3	nn;

	cos = vec2_dot(a, n);
	nn = (t_vec3){n.x * cos, n.y * cos, n.z * cos};
	res = vec3_sub(a, nn);
	return (res);
}

double	ft_resolve_equation(t_equa vs, int *v, t_vec3 pos, t_vec3 d)
{
	float	t[2];
	float	dis[2];
	bool	bol[2];
	double	discriminant;

	discriminant = vs.b * vs.b - 4 * vs.a * vs.c;
	if (discriminant >= 0)
	{
		t[0] = fmin((-vs.b + sqrt(discriminant)) / (2.0 * vs.a), (-vs.b 
					- sqrt(discriminant)) / (2.0 * vs.a));
		t[1] = fmax((-vs.b + sqrt(discriminant)) / (2.0 * vs.a), (-vs.b 
					- sqrt(discriminant)) / (2.0 * vs.a));
		dis[0] = ft_dis(pos, vs.o, vs.n, color_scale(t[0], d));
		dis[1] = ft_dis(pos, vs.o, vs.n, color_scale(t[1], d));
		bol[0] = dis[0] >= 0 && dis[0] <= vs.h && t[0] > 0.0;
		bol[1] = dis[1] >= 0 && dis[1] <= vs.h && t[1] > 0.0;
		if (bol[0])
			return (t[0]);
		if (bol[0] == false & bol[1] == true)
		{
			*v = 1;
			return (t[1]);
		}
	}
	return (-1);
}

double	intersect_cylindre(t_cylinder *cy, t_vec3 pos, t_vec3 d, int *v)
{
	t_equa	vs;
	t_vec3	dir;
	t_vec3	oc;
	double tan;
	
	tan = (cy->diameter /cy.h) * (cy.radius );
	vs.n = vec3_norm(cy->axis);
	dir = handle_coor(d, vs.n);
	vs.o = vec3_sub(pos, cy->center);
	oc = handle_coor(vs.o, vs.n);
	vs.a = vec2_dot(dir, dir);
	vs.b = 2.0 * vec2_dot(oc, dir);
	vs.c = vec2_dot(oc, oc) - (cy->diameter * cy->diameter);
	vs.h = cy->height;
	return (ft_resolve_equation(vs, v, pos, d));
}
