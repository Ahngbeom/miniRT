/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:24:38 by bahn              #+#    #+#             */
/*   Updated: 2022/04/03 20:47:21 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	camera_move(int keycode, t_scene *scene)
{
	printf("keycode : %d\n", keycode);
	if (keycode == 65362)
		scene->camera.orig.y += 0.1;
	else if (keycode == 65364)
		scene->camera.orig.y -= 0.1;
	else if (keycode == 65361)
		scene->camera.orig.x -= 0.1;
	else if (keycode == 65363)
		scene->camera.orig.x += 0.1;
	else
		return (0);
	
	scene->camera.lower_left_corner = vsub(vsub(vsub(scene->camera.orig, vdiv(scene->camera.horizontal, 2)), vdiv(scene->camera.vertical, 2)), vector_init(0, 0, scene->camera.focal_length));
	
	output_scene(scene);
	
	printf("Camera Info\n");
	printf("Origin : %f, %f, %f\n", scene->camera.orig.x, scene->camera.orig.y, scene->camera.orig.z);
	printf("Focal Length : %f\n", scene->camera.focal_length);
	printf("Lower left Corner Point: %f, %f, %f\n", scene->camera.lower_left_corner.x, scene->camera.lower_left_corner.y, scene->camera.lower_left_corner.z);
	return (0);
}

int	camera_zoom(int keycode, int x, int y, t_scene *scene)
{
	printf("mouse keycode : %d (%d, %d)\n", keycode, x, y);
	if (keycode == 4)
		scene->camera.focal_length += 0.1;
	else if (keycode == 5)
		scene->camera.focal_length -= 0.1;
	else
		return (0);
	scene->camera.lower_left_corner = vsub(vsub(vsub(scene->camera.orig, vdiv(scene->camera.horizontal, 2)), vdiv(scene->camera.vertical, 2)), vector_init(0, 0, scene->camera.focal_length));
	output_scene(scene);
	
	printf("Camera Info\n");
	printf("Origin Point: %f, %f, %f\n", scene->camera.orig.x, scene->camera.orig.y, scene->camera.orig.z);
	printf("Focal Length: %f\n", scene->camera.focal_length);
	printf("Lower left Corner Point: %f, %f, %f\n", scene->camera.lower_left_corner.x, scene->camera.lower_left_corner.y, scene->camera.lower_left_corner.z);
	return (0);
}