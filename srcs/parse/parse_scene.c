/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:16:12 by jaeyu             #+#    #+#             */
/*   Updated: 2022/04/20 13:57:48 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_ambient(t_scene *scene, char **split)
{
	// t_ambient *amb;

	if (split_size(split) != 3)
		print_error("Ambient light format: A [ratio] [R,G,B]");
	// amb = malloc(sizeof(t_ambient));
	scene->ambient.ratio = ft_atod(split[1]);
	if (scene->ambient.ratio < 0 || scene->ambient.ratio > 1)
		print_error("Ambient light ratio must be in range [0.0,1.0]");
	parse_color3(&(scene->ambient.color), split[2]);
	if (!check_color3(scene->ambient.color))
		print_error("Ambient RGB must be in range [0,255]");
	// scene->ambient = amb;
}

void	parse_coords(t_vec3 *point, char *vec)
{
	char **coords;
	int		i;
	
	coords = ft_split(vec, ',');
	if (split_size(coords) != 3)
		print_error("Coords format: x,y,z");
	point->x = ft_atod(coords[0]);
	point->y = ft_atod(coords[1]);
	point->z = ft_atod(coords[2]);
	i = -1;
	while (coords[++i] != NULL)
		free(coords[i]);
	free(coords);
}

void	parse_camera(t_scene *scene, char **split)
{
	t_camera *cam;

	if (split_size(split) != 4)
		print_error("Camera usage: C [origin x,y,z] [normal x,y,z] [fov]");
	cam = malloc(sizeof(t_camera));
	// parse_coords(&(scene->camera.orig), split[1]);
	// parse_coords(&(scene->camera.dir), split[2]);
	parse_coords(&(cam->orig), split[1]);
	parse_coords(&(cam->dir), split[2]);
	cam->fov = ft_atoi(split[3]);
	// scene->camera.fov = ft_atoi(split[3]);
	if (cam->fov < 0 || cam->fov > 180)
		print_error("Camera FOV must be in range [0-180]");
	// scene->camera = cam;

	if (scene->camera == NULL)
		scene->camera = ft_lstnew(cam);
	else
		ft_lstadd_back(&scene->camera, ft_lstnew(cam));
}

void	parse_light(t_scene *scene, char **split)
{
	// t_light *light;
	
	if (split_size(split) != 4)
		print_error("Light usage: L [origin x,y,z] [brightness] [R,G,B]");
	// light = malloc(sizeof(t_light));
	parse_coords(&(scene->light.orig), split[1]);
	scene->light.bright_ratio = ft_atod(split[2]);
	parse_color3(&(scene->light.light_color), split[3]);
	if (!check_color3(scene->light.light_color))
		print_error("Light RGB must be in range [0-255]");
	// scene->light = light;
}