/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_structure.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:24:07 by bahn              #+#    #+#             */
/*   Updated: 2022/05/10 00:57:42 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_STRUCTURE_H
# define MINIRT_STRUCTURE_H

# include "minirt.h"

typedef int					t_bool;

typedef struct s_vars		t_vars;
typedef struct s_img_data	t_img_data;

typedef struct s_vec3		t_vec3;
typedef struct s_vec3		t_point3;
typedef struct s_vec3		t_color3;

typedef struct s_ray		t_ray;

typedef struct s_camera		t_camera;

typedef struct s_canvas		t_canvas;

typedef int					t_object_type;
typedef struct s_object		t_object;

typedef struct s_sphere		t_sphere;
typedef struct s_plane		t_plane;
typedef struct s_cylinder	t_cylinder;
typedef struct s_square		t_square;

typedef struct s_hit_record	t_hit_record;

typedef struct s_ambient	t_ambient;
typedef struct s_light		t_light;

typedef struct s_scene		t_scene;

struct s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
};

struct s_vars
{
	void		*mlx;
	void		*win;
	t_img_data	*img_data;
};

struct s_vec3
{
	double	x;
	double	y;
	double	z;
};

struct s_ray
{
	t_point3	orig;
	t_vec3		dir;
};

struct s_camera
{
	double		viewport_height;
	double		viewport_width;

	t_point3	orig;
	t_vec3		horizontal;
	t_vec3		vertical;
	t_vec3		lower_left_corner;

	t_vec3		dir;

	int			fov;

	t_vec3		vup;
	t_vec3		w;
	t_vec3		u;
	t_vec3		v;
};

struct s_canvas
{
	int		width;
	int		height;
	double	aspect_ratio;
};

struct s_sphere
{
	t_point3	center;
	double		diameter;
	double		radius;
};

struct s_plane
{
	t_point3	coord;
	t_vec3		normal;
};

struct s_cylinder
{
	t_point3	coord;
	t_vec3		dir;
	double		diameter;
	double		height;

	t_point3	coord_top;
	t_point3	coord_bot;

	double		cy_t;
	double		cy_t_disk_top;
	double		cy_t_disk_bot;
};

struct s_square
{
	t_point3	center;
	t_vec3		normal;
	double		side_length;
};

struct s_object
{
	t_object_type	type;
	void			*element;
	t_color3		color;
	void			*next;
};

struct s_hit_record
{
	t_point3	p;
	t_vec3		normal;
	double		tmin;
	double		tmax;
	double		t;
	int			front_face;
	t_color3	albedo;
};

struct	s_ambient
{
	t_color3	color;
	double		ratio;
};

struct s_light
{
	t_point3	orig;
	t_color3	light_color;
	double		bright_ratio;
};

struct s_scene
{
	t_vars			*vars;
	t_list			*camera;
	t_canvas		canvas;
	t_ray			ray;
	t_hit_record	rec;

	t_object		*objects;
	t_ambient		ambient;
	t_list			*lights;
};

#endif
