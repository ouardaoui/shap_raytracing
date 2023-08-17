/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 11:48:56 by hahadiou          #+#    #+#             */
/*   Updated: 2023/08/17 07:01:55 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

	
void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

void create_scene(t_scene *scene, char *filename, mlx_t *mlx, mlx_image_t *image)
{
    bzero(scene, sizeof(t_scene));
    printf("-----PARSING FILE----: %s\n", filename);
    printf("\n\n");
    
	//mlx = mlx_init(WIDTH, HEIGHT, "Ray Tracing", true);
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, image, 0, 0);
	mlx_loop_hook(mlx, ft_hook, mlx);
  parse_scene(scene, filename);
}

int main(int ac, char **av)
{
		mlx_t *mlx;
   t_scene scene;
   mlx_image_t* image; 
		int i = 0;
	if (ac != 2)
		return (1);
	mlx = mlx_init(WIDTH, HEIGHT, "Ray Tracing", true); 
	create_scene(&scene, av[1], mlx, image);
	//render_scene(&scene);
	
	t_plane *li = scene.object.pl_lst;
	while(li)
	{
		printf("%d\n", i++);	
		li = li->next;
	}	
	mlx_loop(mlx);
	mlx_terminate(mlx);
	
	return (0);
}