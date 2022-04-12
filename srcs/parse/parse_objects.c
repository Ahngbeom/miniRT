/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyu <jaeyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:07:57 by jaeyu             #+#    #+#             */
/*   Updated: 2022/04/09 16:23:50 by jaeyu            ###   ########.fr       */
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
	sphere->diameter2 = pow(sphere->diameter, 2.0);
	
	object = object_init(SPHERE, sphere, color_init(0, 0, 0), color_init(0, 0.5, 0));

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
	parse_coords(&(plane->normal), split[2]);
	
	object = object_init(PLANE, plane, color_init(0, 0, 0), color_init(0, 0, 0));
	
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
	parse_coords(&(cylinder->normal), split[2]);
	cylinder->diameter = ft_atod(split[3]);
	cylinder->height = ft_atod(split[4]);
	cylinder->radius = cylinder->diameter / 2;
	cylinder->top_center = vsum(cylinder->coord, vmul_t(cylinder->height / 2, cylinder->normal));
	cylinder->bottom_center = vsub(cylinder->coord, vmul_t(cylinder->height / 2, cylinder->normal));

	object = object_init(CYLINDER, cylinder, color_init(0, 0, 0), color_init(0, 0, 0));

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