/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseol <jseol@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:24:38 by bahn              #+#    #+#             */
/*   Updated: 2022/05/04 17:36:49 by jseol            ###   ########.fr       */
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

	cam = scene->camera->content;
	printf("mouse keycode : %d (%d, %d)\n", keycode, x, y);
	(void)x;
	(void)y;
	if (keycode == 4)
		cam->lower_left_corner.z -= 0.1;
	else if (keycode == 5)
		cam->lower_left_corner.z += 0.1;
	else if (keycode == 1)
	{
		scene->ray = ray_primary(cam, (double)x / scene->canvas.width, \
										(double)y / scene->canvas.height);
		if (hit(scene->objects, &scene->ray, &scene->rec) == TRUE)
			printf("TRUE\n");
		else
			printf("FALSE\n");
	}
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
	printf("Camera Info\n");						// 25줄 줄이기 위해서 info 출력물을 줄여야 할거 같습니다.
	printf("Camera View point : %f, %f, %f\n", cam->orig.x, cam->orig.y, \
		cam->orig.z);
	printf("Camera Direction : %f, %f, %f\n", cam->dir.x, cam->dir.y, \
		cam->dir.z);
	printf("Camera FOV : %d\n", cam->fov);
	printf("Camera View up : %f, %f, %f\n", cam->vup.x, cam->vup.y, cam->vup.z);
	printf("Camera w : %f, %f, %f\n", cam->w.x, cam->w.y, cam->w.z);
	printf("Camera u : %f, %f, %f\n", cam->u.x, cam->u.y, cam->u.z);
	printf("Camera v : %f, %f, %f\n", cam->v.x, cam->v.y, cam->v.z);
	printf("Camera horizontal : %f, %f, %f\n", cam->horizontal.x, \
		cam->horizontal.y, cam->horizontal.z);
	printf("Camera vertical : %f, %f, %f\n", cam->vertical.x, \
		cam->vertical.y, cam->vertical.z);
	printf("Lower left Corner Point: %f, %f, %f\n\n",
		cam->lower_left_corner.x, cam->lower_left_corner.y, \
		cam->lower_left_corner.z);
	output_scene(scene);
	return (0);
}
