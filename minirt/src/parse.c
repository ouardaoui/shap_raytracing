/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 03:27:49 by aouardao          #+#    #+#             */
/*   Updated: 2023/08/17 06:44:42 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"


void	parse_ids(t_scene *scene, char **split)
{
	if (!strcmp(split[0], "C"))
		parse_cam(scene, split);
	else if (!strcmp(split[0], "A"))
		parse_amb(scene, split);
	else if (!strcmp(split[0], "L"))
		parse_light(scene, split);
	else if (!strcmp(split[0], "sp"))
		parse_sphere(scene, split);
	else if (!strcmp(split[0], "pl"))
		parse_plane(scene, split);
	else if (!strcmp(split[0], "cy"))
		parse_cylinder(scene, split);
	else
		dprintf(2, "Invalid Id\n");
}	
		
int	parse_scene(t_scene *scene, char *filename)
{
	int		fd;
	char	*line[2];
	char	**split;

	fd = open(filename, O_RDONLY);
	if (fd < 2)
	{
		dprintf(2, "Error opening file\n");
		exit(1);
	}
	while (-42)
	{
		line[0] = get_next_line(fd);
		if (line[0] == NULL)
			break ;
		line[1] = ft_strtrim(line[0], " \t");
		split = ft_split(line[1], ' ');
		if (split == NULL)
		{
			dprintf(2, "Inv Memeory\n");
			exit (1);
		}
		parse_ids(scene, split);
	}
	return (0);
}