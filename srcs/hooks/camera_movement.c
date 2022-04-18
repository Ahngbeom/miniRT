/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:24:38 by bahn              #+#    #+#             */
/*   Updated: 2022/04/18 19:37:28 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	camera_move(int keycode, t_scene *scene)
{
	printf("keycode : %d\n", keycode);
	if (keycode == 65362 || keycode == 126)
		// scene->camera.orig.y += 0.1;
		scene->camera.dir.y += 0.1;
	else if (keycode == 65364 || keycode == 125)
		scene->camera.dir.y -= 0.1;
	else if (keycode == 65361 || keycode == 123)
		scene->camera.dir.x -= 0.1;
	else if (keycode == 65363 || keycode == 124)
		scene->camera.dir.x += 0.1;
	else
		return (0);
	init_camera(scene, scene->camera.fov);
	output_scene(scene);
	return (0);
}

int	camera_zoom(int keycode, int x, int y, t_scene *scene)
{
	// printf("mouse keycode : %d (%d, %d)\n", keycode, x, y);
	(void)x;
	(void)y;
	if (keycode == 4)
		init_camera(scene, scene->camera.fov + 5);
	else if (keycode == 5)
		init_camera(scene, scene->camera.fov - 5);
	else
		return (0);
	output_scene(scene);
	return (0);
}