/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:11:41 by bahn              #+#    #+#             */
/*   Updated: 2022/05/05 00:58:44 by bahn             ###   ########.fr       */
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
