/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:24:38 by bahn              #+#    #+#             */
/*   Updated: 2022/05/05 11:43:12 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	camera_move(int keycode, t_scene *scene)
{
	t_camera	*cam;

	cam = scene->camera->content;
	if ((keycode == 32 || keycode == 49))
		return (camera_switch(scene));
	else if (keycode == 65362 || keycode == 126)
		cam->lower_left_corner.y += 0.1;
	else if (keycode == 65364 || keycode == 125)
		cam->lower_left_corner.y -= 0.1;
	else if (keycode == 65361 || keycode == 123)
		cam->lower_left_corner.x -= 0.1;
	else if (keycode == 65363 || keycode == 124)
		cam->lower_left_corner.x += 0.1;
	else
		return (0);
	output_scene(scene);
	return (0);
}

int	camera_zoom(int keycode, int x, int y, t_scene *scene)
{
	t_camera	*cam;

	(void)x;
	(void)y;
	cam = scene->camera->content;
	if (keycode == 4)
		cam->lower_left_corner.z -= 0.1;
	else if (keycode == 5)
		cam->lower_left_corner.z += 0.1;
	else
		return (0);
	output_scene(scene);
	return (0);
}

int	camera_switch(t_scene *scene)
{
	t_list		*tmp;
	t_camera	*cam;

	if (scene->camera->next != NULL)
	{
		tmp = scene->camera;
		scene->camera = scene->camera->next;
		tmp->next = NULL;
		ft_lstadd_back(&scene->camera, tmp);
	}
	cam = scene->camera->content;
	print_caminfo(cam);
	output_scene(scene);
	return (0);
}
