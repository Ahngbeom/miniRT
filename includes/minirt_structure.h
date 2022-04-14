/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_structure.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:24:07 by bahn              #+#    #+#             */
/*   Updated: 2022/04/14 22:20:36 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_STRUCTURE_H
# define MINIRT_STRUCTURE_H

typedef struct s_vars		t_vars;
typedef	struct s_img_data	t_img_data;

typedef struct s_vec3		t_vec3;
typedef struct s_vec3		t_point3;
typedef struct s_vec3		t_color3;

typedef struct s_ray		t_ray;

typedef	struct s_camera		t_camera;

typedef	struct s_canvas		t_canvas;

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
	void		*mlx; // miniLibX 포인터
	void		*win; // miniLibX Window 포인터
	t_img_data	*img_data; // miniLibX Image 포인터
};

struct s_vec3
{
	double	x;
	double	y;
	double	z;
};

struct s_ray
{
	t_point3	orig;	// 광선의 원점
	t_vec3		dir;	// 광선의 방향 벡터
};

struct s_camera
{
	double viewport_height;	// Viewport 세로 길이
	double viewport_width; // Viewport 가로 길이
	
	t_point3	orig;
	t_vec3		horizontal; // 수평 길이 벡터
	t_vec3		vertical; // 수직 길이 벡터
	t_vec3		lower_left_corner; // 왼쪽 아래 코너 점
	
	t_vec3		dir;

	int			fov;

	t_vec3		vup;
	t_vec3		w;
	t_vec3		u;
	t_vec3		v;
};

struct s_canvas
{
	int		width; // 캔버스 너비
	int		height; // 캔버스 높이
	double	aspect_ratio; // 종횡비
};

struct s_sphere
{
	t_point3	center;
	double		diameter;
	double		radius;
};

struct s_plane
{
	t_point3	coord;	// 평면 상 어느 한 지점.
	t_vec3		dir;	// 평면이 가리키는 방향, 기울임 방향 및 정도
};

struct s_cylinder
{
	t_point3	coord;
	t_vec3		dir;
	double		diameter;
	double		height;
	
	t_point3	coord_top;
	t_point3	coord_bot;
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
    t_point3	p;          // 교점의 좌표
    t_vec3		normal;     // 교점에서의 법선 벡터
    double		tmin;       // 오브젝트가 카메라 뒤쪽에 있을 경우 최소 거리
    double		tmax;       // 오브젝트가 카메라 앞쪽에 있을 경우 최대 거리 
    double		t;          // 광선의 원점과 교점 사이의 거리
    int			front_face; // 광선의 방향벡터와 교점의 법선벡터 간 내적 연산하여 광선이 오브젝트에 부딪히는 면의 위치 판단
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
	t_camera		camera;
	t_canvas		canvas;
	t_ray			ray;
	t_hit_record	rec;

	t_object		*objects;
	t_ambient		ambient; // 주변 조명
	t_light			light; // 광원
};

#endif