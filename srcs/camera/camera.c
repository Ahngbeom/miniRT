/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:11:41 by bahn              #+#    #+#             */
/*   Updated: 2022/05/05 11:42:51 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_camera(t_scene *scene)
{
	t_list		*lst_cam;
	t_camera	*cam;
	double		view_angle;
	double		h;

	lst_cam = scene->camera;
	while (lst_cam != NULL)
	{
		cam = lst_cam->content;
		view_angle = cam->fov * MINIRT_PI / 180.0;
		h = tan(view_angle / 2.0);
		cam->viewport_height = 2.0 * h;
		cam->viewport_width = cam->viewport_height * scene->canvas.aspect_ratio;
		cam->vup = vector_init(0, 1, 0);
		cam->w = vunit(vmul_t(-1, cam->dir));
		cam->u = vunit(vcross(cam->vup, cam->w));
		cam->v = vunit(vcross(cam->w, cam->u));
		cam->horizontal = vmul_t(cam->viewport_width, cam->u);
		cam->vertical = vmul_t(cam->viewport_height, cam->v);
		cam->lower_left_corner = vsub(vsub(vsub(cam->orig, \
											vdiv(cam->horizontal, 2)), \
										vdiv(cam->vertical, 2)), \
									cam->w);
		lst_cam = lst_cam->next;
	}
}

void	set_camera(t_scene *scene)
{
	t_camera	*cam;
	double		view_angle;
	double		h;

	cam = scene->camera->content;
	view_angle = cam->fov * MINIRT_PI / 180.0;
	h = tan(view_angle / 2.0);
	cam->viewport_height = 2.0 * h;
	cam->viewport_width = cam->viewport_height * scene->canvas.aspect_ratio;
	cam->vup = vector_init(0, 1, 0);
	cam->w = vunit(vmul_t(-1.0, cam->dir));
	cam->u = vunit(vcross(cam->vup, cam->w));
	cam->v = vunit(vcross(cam->w, cam->u));
	cam->horizontal = vmul_t(cam->viewport_width, cam->u);
	cam->vertical = vmul_t(cam->viewport_height, cam->v);
	cam->lower_left_corner = vsub(vsub(vsub(cam->orig, \
											vdiv(cam->horizontal, 2)), \
										vdiv(cam->vertical, 2)), \
									cam->w);
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
