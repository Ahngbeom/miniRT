/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseol <jseol@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:07:57 by jaeyu             #+#    #+#             */
/*   Updated: 2022/05/04 16:08:49 by jseol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_sphere(t_scene *scene, char **split)
{
	t_object	*object;
	t_sphere	*sphere;

	if (split_size(split) != 4)
		print_error("Sphere format: sp [origin x,y,z] [diameter] [R,G,B]");
	// object = malloc(sizeof(t_object));
	sphere = malloc(sizeof(t_sphere));
	parse_coords(&(sphere->center), split[1]);
	sphere->diameter = ft_atod(split[2]);
	sphere->radius = sphere->diameter / 2.0;

	object = object_init(SPHERE, sphere, color_init(0, 0, 0));

	parse_color3(&(object->color), split[3]);
	if (!check_color3(object->color))
		print_error("Sphere RGB must be in range [0,255]");

	if (scene->objects == NULL)
		scene->objects = object;
	else
		object_add(&scene->objects, object);
	// sphere->diameter = ft_atod(split[2]);
	// parse_color3(&(sphere->rgb), split[3]);

	// scene->objects->type = SPHERE;
	// scene->objects->element = sphere;
	// ft_lstadd_back(&(scene->object), ft_lstnew(object));
}

void	parse_plane(t_scene *scene, char **split)
{
	t_object	*object;
	t_plane		*plane;

	if (split_size(split) != 4)
		print_error("Plane format: pl [origin x,y,z] [normal x,y,z] [R,G,B]");
	// object = malloc(sizeof(t_object));
	plane = malloc(sizeof(t_plane));
	parse_coords(&(plane->coord), split[1]);
	// parse_coords(&(plane->direction), split[2]);
	parse_coords(&(plane->dir), split[2]);

	object = object_init(PLANE, plane, color_init(0, 0, 0));

	parse_color3(&(object->color), split[3]);
	if (!check_color3(object->color))
		print_error("Plane RGB must be in range [0,255]");

	if (scene->objects == NULL)
		scene->objects = object;
	else
		object_add(&scene->objects, object);

	// object->type = PLANE;
	// object->element = plane;
	// ft_lstadd_back(&(scene->object), ft_lstnew(object));
}

void	parse_cylinder(t_scene *scene, char **split)
{
	t_object	*object;
	t_cylinder	*cylinder;

	if (split_size(split) != 6)
		print_error("Cylinder format: cy [x,y,z] [normal x,y,z] [d] [h] [RGB]");
	// object = malloc(sizeof(t_object));

	cylinder = malloc(sizeof(t_cylinder));
	parse_coords(&(cylinder->coord), split[1]);
	// parse_coords(&(cylinder->direction), split[2]);
	parse_coords(&(cylinder->dir), split[2]);
	cylinder->diameter = ft_atod(split[3]);
	cylinder->height = ft_atod(split[4]);
	// 원기둥의 중심점에서 원기둥의 방향에 맞게 원기둥의 높이/2 만큼 더해주거나 빼주어 원기둥의 윗면/아랫면의 좌표를 구한다.
	cylinder->coord_top = vsum(cylinder->coord, vmul_t(cylinder->height / 2, cylinder->dir));
	cylinder->coord_bot = vsub(cylinder->coord, vmul_t(cylinder->height / 2, cylinder->dir));
	object = object_init(CYLINDER, cylinder, color_init(0, 0, 0));

	parse_color3(&(object->color), split[5]);
	if (!check_color3(object->color))
		print_error("Cylinder RGB must be in range [0,255]");

	if (scene->objects == NULL)
		scene->objects = object;
	else
		object_add(&scene->objects, object);
	// object->type = CYLINDER;
	// object->element = cylinder;
	// ft_lstadd_back(&(scene->object), ft_lstnew(object));
}
