/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_switch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:24:38 by bahn              #+#    #+#             */
/*   Updated: 2022/04/20 14:04:32 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	camera_switch(int keycode, t_scene *scene)
{
	t_list		*tmp;
	t_camera	*cam;
	printf("keycode : %d\n", keycode);
	if ((keycode == 32 || keycode == 49) && ft_lstsize(scene->camera) > 1)
	{
		tmp = scene->camera;
		// ft_lstlast(scene->camera)->next = tmp;
		scene->camera = scene->camera->next;
		tmp->next = NULL;
		ft_lstadd_back(&scene->camera, tmp);
		
		cam = scene->camera->content;
		printf("Camera Info\n");
		printf("Camera View point : %f, %f, %f\n", cam->orig.x, cam->orig.y, cam->orig.z);
		printf("Camera Direction : %f, %f, %f\n", cam->dir.x, cam->dir.y, cam->dir.z);
		printf("Camera FOV : %d\n", cam->fov);
		printf("Camera View up : %f, %f, %f\n", cam->vup.x, cam->vup.y, cam->vup.z);
		printf("Camera w : %f, %f, %f\n", cam->w.x, cam->w.y, cam->w.z);
		printf("Camera u : %f, %f, %f\n", cam->u.x, cam->u.y, cam->u.z);
		printf("Camera v : %f, %f, %f\n", cam->v.x, cam->v.y, cam->v.z);
		printf("Camera horizontal : %f, %f, %f\n", cam->horizontal.x, cam->horizontal.y, cam->horizontal.z);
		printf("Camera vertical : %f, %f, %f\n", cam->vertical.x, cam->vertical.y, cam->vertical.z);
		printf("Lower left Corner Point: %f, %f, %f\n\n", cam->lower_left_corner.x, cam->lower_left_corner.y, cam->lower_left_corner.z);
	
		output_scene(scene);
	}
	return (0);
}
