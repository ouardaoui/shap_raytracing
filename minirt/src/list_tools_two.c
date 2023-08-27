/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 19:40:16 by aouardao          #+#    #+#             */
/*   Updated: 2023/08/27 19:45:40 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	add_sphere_to_back(t_sphere **lst, t_sphere *new_node)
{
	t_sphere	*current;

	if (*lst == NULL)
		*lst = new_node;
	else
	{
		current = *lst;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

void	add_cylinder_to_back(t_cylinder **lst, t_cylinder *new_node)
{
	t_cylinder	*current;

	if (*lst == NULL)
		*lst = new_node;
	else
	{
		current = *lst;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

void	add_plane_to_back(t_plane **lst, t_plane *new_node)
{
	t_plane	*current;

	if (*lst == NULL)
		*lst = new_node;
	else
	{
		current = *lst;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

void	add_light_to_back(t_light **lst, t_light *new_node)
{
	t_light	*current;

	if (*lst == NULL)
		*lst = new_node;
	else
	{
		current = *lst;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}
