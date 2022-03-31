/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyu <jaeyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 13:25:42 by jaeyu             #+#    #+#             */
/*   Updated: 2022/03/31 15:04:34 by jaeyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>	//임시
# include "libft.h"
# include "mlx.h"

# define SPHERE 10
# define PLANE 11
# define CYLINDER 12

typedef struct	s_vec3			t_vec3;
typedef struct	s_vec3			t_color3;

struct s_vec3
{
	double		x;
	double		y;
	double		z;
};

typedef struct	s_ambient
{
	t_color3	rgb;
	double		ratio;
}				t_ambient;

typedef struct	s_camera
{
	t_vec3		viewpoint;
	t_vec3		direction;	// 방향벡터
	int			fov;		// 수평 시야 범위
}				t_camera;

typedef struct	s_light
{
	t_vec3		point;	//
	double		ratio;
	t_color3	rgb;
}				t_light;

typedef struct	s_object
{
	int			type;
	void		*element;
}				t_object;

typedef struct	s_sphere
{
	t_vec3		center;
	double		diameter;
	t_color3	rgb;
}				t_sphere;

typedef struct	s_plane
{
	t_vec3		coord;
	t_vec3		direction;
	t_color3	rgb;
}				t_plane;

typedef struct	s_cylinder
{
	t_vec3		coord;
	t_vec3		direction;
	double		diameter;
	double		height;
	t_color3	rgb;
}				t_cylinder;

typedef struct			s_scene
{
	t_ambient			*ambient;
	t_camera			*camera;
	t_light				*light;
	t_list				*object;
}						t_scene;

/*
parse_file.c
*/
t_scene	*parse_file(char *filename);
void	parse_line(t_scene *scene, char **split);
void	init_scene(t_scene *scene);
int		check_line(char *line);
int		allowed_symbol(char c);

/*
parse_scene
*/
void	parse_coords(t_vec3 *point, char *vec);
void	parse_light(t_scene *scene, char **split);
void	parse_camera(t_scene *scene, char **split);
void	parse_ambient(t_scene *scene, char **split);

/*
parse_objects
*/
void	parse_sphere(t_scene *scene, char **split);
void	parse_plane(t_scene *scene, char **split);
void	parse_cylinder(t_scene *scene, char **split);

/*
parse_color3
*/
int		check_color3(t_color3 rgb);
void	parse_color3(t_color3 *ret, char *color);

/*
split_utils
*/
int		split_size(char **split);
char	**ft_split2(char const *s, char c1, char c2);

#endif
