/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 04:02:49 by aouardao          #+#    #+#             */
/*   Updated: 2023/08/17 06:34:31 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void add_sphere_to_back(t_sphere **lst, t_sphere *new_node)
{
    if (*lst == NULL) 
        *lst = new_node;
	else 
	{
        t_sphere *current = *lst;
        while (current->next != NULL)
            current = current->next;
        current->next = new_node;
    }
}
void add_cylinder_to_back(t_cylinder **lst, t_cylinder *new_node)
{
    if (*lst == NULL) 
        *lst = new_node;
	else 
	{
        t_cylinder *current = *lst;
        while (current->next != NULL)
            current = current->next;
        current->next = new_node;
    }
}
void add_plane_to_back(t_plane **lst, t_plane *new_node)
{
    if (*lst == NULL) 
        *lst = new_node;
	else 
	{
        t_plane *current = *lst;
        while (current->next != NULL)
            current = current->next;
        current->next = new_node;
    }
}
void add_light_to_back(t_light **lst, t_light *new_node)
{
    if (*lst == NULL) 
        *lst = new_node;
	else 
	{
        t_light *current = *lst;
        while (current->next != NULL)
            current = current->next;
        current->next = new_node;
    }
}
t_sphere *create_sphere_node() {

	t_sphere *new_node = (t_sphere *)malloc(sizeof(t_sphere));
    if (new_node == NULL) {
        return NULL;
    }
	new_node->next = NULL;
    return (new_node);
}

t_cylinder *create_cylinder_node() {

	t_cylinder *new_node = (t_cylinder *)malloc(sizeof(t_cylinder));
    if (new_node == NULL) {
        return NULL;
    }
	new_node->next = NULL;
    return (new_node);
}

t_plane *create_plane_node() {

	t_plane *new_node = (t_plane *)malloc(sizeof(t_plane));
    if (new_node == NULL) {
        return NULL;
    }
	new_node->next = NULL;
    return (new_node);
}

t_light *create_light_node() {

	t_light *new_node = (t_light *)malloc(sizeof(t_light));
    if (new_node == NULL) {
        return NULL;
    }
	new_node->next = NULL;
    return (new_node);
}