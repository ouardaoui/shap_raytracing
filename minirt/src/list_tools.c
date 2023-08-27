/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 04:02:49 by aouardao          #+#    #+#             */
/*   Updated: 2023/08/27 19:44:05 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_sphere	*create_sphere_node(void)
{
	t_sphere	*new_node;

	new_node = (t_sphere *)malloc(sizeof(t_sphere));
	if (new_node == NULL)
	{
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

t_cylinder	*create_cylinder_node(void)
{
	t_cylinder	*new_node;

	new_node = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (new_node == NULL)
	{
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

t_plane	*create_plane_node(void)
{
	t_plane	*new_node;

	new_node = (t_plane *)malloc(sizeof(t_plane));
	if (new_node == NULL)
	{
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

t_light	*create_light_node(void)
{
	t_light	*new_node;

	new_node = (t_light *)malloc(sizeof(t_light));
	if (new_node == NULL)
	{
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}
