/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyu <jaeyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:16:12 by jaeyu             #+#    #+#             */
/*   Updated: 2022/03/30 19:13:13 by jaeyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		check_color3(t_color3 rgb)
{
	if (rgb.x < 0 || rgb.x > 255 || rgb.y < 0 || rgb.y > 255 || rgb.z < 0 ||
	rgb.z > 255)
		return (0);
	return (1);
}

void	parse_color3(t_color3 *ret, char *color)
{
	char **split;

	split = ft_split(color, ',');
	if (split_size(split) != 3)
		printf("Color format: R,G,B");
	ret->x = (double)ft_atoi(split[0]);
	ret->y = (double)ft_atoi(split[1]);
	ret->z = (double)ft_atoi(split[2]);
}

void	parse_ambient(t_scene *scene, char **split)
{
	t_ambient *amb;

	if (split_size(split) != 3)
		printf("Ambient light format: A [ratio] [R,G,B]");
	amb = malloc(sizeof(t_ambient));
	amb->ratio = ft_atod(split[1]);
	if (amb->ratio < 0 || amb->ratio > 1)
		printf("Ambient light ratio must be in range [0.0,1.0]");
	parse_color3(&(amb->rgb), split[2]);
	if (!check_color3(amb->rgb))
		printf("Ambient RGB must be in range [0,255]");
	scene->ambient = amb;
}

void	parse_coords(t_vec3 *point, char *vec)
{
	char **coords;

	coords = ft_split(vec, ',');
	if (split_size(coords) != 3)
		printf("Coords format: x,y,z");
	point->x = ft_atod(coords[0]);
	point->y = ft_atod(coords[1]);
	point->z = ft_atod(coords[2]);
}

void	parse_camera(t_scene *scene, char **split)
{
	t_camera *cam;

	if (split_size(split) != 4)
		printf("Camera usage: C [origin x,y,z] [normal x,y,z] [fov]");
	cam = malloc(sizeof(t_camera));
	parse_coords(&(cam->viewpoint), split[1]);
	parse_coords(&(cam->direction), split[2]);
	cam->fov = ft_atoi(split[3]);
	if (cam->fov < 0 || cam->fov > 180)
		printf("Camera FOV must be in range [0-180]");
	scene->camera = cam;
}

void	parse_light(t_scene *scene, char **split)
{
	t_light *light;
	
	if (split_size(split) != 4)
		printf("Light usage: L [origin x,y,z] [brightness] [R,G,B]");
	light = malloc(sizeof(t_light));
	parse_coords(&(light->point), split[1]);
	light->ratio = ft_atod(split[2]);
	parse_color3(&(light->rgb), split[3]);
	if (!check_color3(light->rgb))
		printf("Light RGB must be in range [0-255]");
	scene->light = light;
}