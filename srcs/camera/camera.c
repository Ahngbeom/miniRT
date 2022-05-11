/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseol <jseol@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:11:41 by bahn              #+#    #+#             */
/*   Updated: 2022/05/11 13:09:26 by jseol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_camera(t_scene *scene)
{
	t_list		*lst_cam;

	lst_cam = scene->camera;
	if (lst_cam == NULL)
		print_error("Camera doesn't not exist.");
	while (lst_cam != NULL)
	{
		set_camera(lst_cam->content, scene->canvas.aspect_ratio);
		lst_cam = lst_cam->next;
	}
}

void	set_camera(t_camera *camera, double aspect_ratio)
{
	double		view_angle;
	double		h;

	view_angle = camera->fov * MINIRT_PI / 180.0;
	h = tan(view_angle / 2.0);
	camera->viewport_height = 2.0 * h;
	camera->viewport_width = camera->viewport_height * aspect_ratio;
	camera->vup = vector_init(0, 1, 0);
	camera->w = vunit(vmul_t(-1.0, camera->dir));
	camera->u = vunit(vcross(camera->vup, camera->w));
	camera->v = vunit(vcross(camera->w, camera->u));
	camera->horizontal = vmul_t(camera->viewport_width, camera->u);
	camera->vertical = vmul_t(camera->viewport_height, camera->v);
	camera->lower_left_corner = vsub(vsub(vsub(camera->orig, \
											vdiv(camera->horizontal, 2)), \
										vdiv(camera->vertical, 2)), \
									camera->w);
}

void	print_caminfo(t_camera *cam)
{
	printf("Camera Info\n");
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
}
