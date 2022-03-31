/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyu <jaeyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:07:57 by jaeyu             #+#    #+#             */
/*   Updated: 2022/03/31 15:04:04 by jaeyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse_sphere(t_scene *scene, char **split)
{
	t_object	*object;
	t_sphere	*sphere;

	if (split_size(split) != 4)
		printf("Sphere format: sp [origin x,y,z] [diameter] [R,G,B]");
	object = malloc(sizeof(t_object));
	sphere = malloc(sizeof(t_sphere));
	parse_coords(&(sphere->center), split[1]);
	sphere->diameter = ft_atod(split[2]);
	parse_color3(&(sphere->rgb), split[3]);
	if (!check_color3(sphere->rgb))
		printf("Sphere RGB must be in range [0,255]");
	object->type = SPHERE;
	object->element = sphere;
	ft_lstadd_back(&(scene->object), ft_lstnew(object));
}

void	parse_plane(t_scene *scene, char **split)
{
	t_object	*object;
	t_plane		*plane;

	if (split_size(split) != 4)
		printf("Plane format: pl [origin x,y,z] [normal x,y,z] [R,G,B]");
	object = malloc(sizeof(t_object));
	plane = malloc(sizeof(t_plane));
	parse_coords(&(plane->coord), split[1]);
	parse_coords(&(plane->direction), split[2]);
	parse_color3(&(plane->rgb), split[3]);
	if (!check_color3(plane->rgb))
		printf("Plane RGB must be in range [0,255]");
	object->type = PLANE;
	object->element = plane;
	ft_lstadd_back(&(scene->object), ft_lstnew(object));
}

void	parse_cylinder(t_scene *scene, char **split)
{
	t_object	*object;
	t_cylinder	*cylinder;

	if (split_size(split) != 6)
		printf("Cylinder format: cy [x,y,z] [normal x,y,z] [d] [h] [RGB]");
	object = malloc(sizeof(t_object));
	cylinder = malloc(sizeof(t_cylinder));
	parse_coords(&(cylinder->coord), split[1]);
	parse_coords(&(cylinder->direction), split[2]);
	cylinder->diameter = ft_atod(split[3]);
	cylinder->height = ft_atod(split[4]);
	parse_color3(&(cylinder->rgb), split[5]);
	if (!check_color3(cylinder->rgb))
		printf("Cylinder RGB must be in range [0,255]");
	object->type = CYLINDER;
	object->element = cylinder;
	ft_lstadd_back(&(scene->object), ft_lstnew(object));

}