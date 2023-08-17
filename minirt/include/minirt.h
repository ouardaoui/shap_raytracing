/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:02:02 by hahadiou          #+#    #+#             */
/*   Updated: 2023/05/25 20:20:54 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "MLX42.h"
# include <math.h>
# include <string.h>
# include <stdbool.h>
# include "utils.h"

#define WIDTH 800
#define HEIGHT 600

enum e_error t_error;

enum e_error {
    inv_ext,
    inv_file
};
typedef struct 	s_scene		t_scene;
typedef struct 	s_set		t_set;
typedef struct 	s_cam		t_cam;
typedef struct	s_vec3		t_vec3;
typedef struct	s_am_light	t_am_light;
typedef struct	s_light		t_light;
typedef struct	s_object	t_object;
typedef struct s_sphere		t_sphere;
typedef struct s_cylinder	t_cylinder;
typedef struct s_plane		t_plane;

struct s_vec3
{
	double	x;
	double	y;
	double	z;
};

struct s_cam
{
	bool	set;
	t_vec3	pos;
	t_vec3	dir;
	t_vec3	pos_initial;
	t_vec3	dir_initial;
	int		fov;
};

struct s_am_light
{
	bool	set;
	double	brightness;
	t_vec3	color;
};

struct s_light
{
	double	set;
	t_vec3	pos;
	double	ratio;
	t_vec3	color;
    t_light *next;
};

struct s_sphere	
{
	t_vec3		center;
	double		radius;
	t_vec3		color;
	double		set;
	t_sphere	*next;
};

struct s_plane
{
	t_vec3	point;
	t_vec3	normal;
	t_vec3	color;
	double	set;
	t_plane	*next;
};

struct s_cylinder
{
    t_vec3 		center;
    t_vec3 		axis;
    double 		diameter;
    double		height;
    t_vec3 		color;
    double 		set;
	t_cylinder	*next;
};

struct s_object
{
	t_sphere	*sp_lst;
	t_cylinder	*cy_lst;
	t_plane		*pl_lst;
    t_light     *li_lst;
};

struct s_scene
{
	t_object	object;
	int			width;
    int			height;
    t_am_light 	amb;
    t_cam 		cam;
    t_light 	light;
    t_sphere 	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
};

typedef struct s_mlx
{
	mlx_image_t		*image;
	mlx_t			*mlx;
}	t_mlx;

typedef struct s_data
{
	t_mlx	*mlx;
	t_scene	*scene;	
}	t_data;

void	ft_putstr_fd(char *s, int fd);
int	parse_scene(t_scene *scene, char *filename);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_norm(t_vec3 a);
void	parse_cam(t_scene *scene, char **split);
void	parse_amb(t_scene *scene, char **split);
void	parse_light(t_scene *scene, char **split);
int	ft_array_len(char **arr);
void	stod(char *s, double *res);
void	parse_color(char *s, t_vec3 *color);
t_vec3	color_scale(double f, t_vec3 c1);
void add_sphere_to_back(t_sphere **lst, t_sphere *new_node);
void	parse_sphere(t_scene *scene, char **split);
void	parse_plane(t_scene *scene, char **split);
void	parse_cylinder(t_scene *scene, char **split);
void	parse_vec3(char *s, t_vec3 *vec3);
void	stoi(char *s, int min, int max, int *res);
t_sphere *create_sphere_node();    
t_cylinder *create_cylinder_node() ;
void add_cylinder_to_back(t_cylinder **lst, t_cylinder *new_node);
void add_plane_to_back(t_plane **lst, t_plane *new_node);
t_plane *create_plane_node() ;
void add_light_to_back(t_light **lst, t_light *new_node);
t_light *create_light_node() ;

#endif // MINIRT_H
