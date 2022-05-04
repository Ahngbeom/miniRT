/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseol <jseol@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:11:41 by bahn              #+#    #+#             */
/*   Updated: 2022/05/04 16:07:08 by jseol            ###   ########.fr       */
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
		view_angle = cam->fov * MINIRT_PI / 180.0; // 시야각
		h = tan(view_angle / 2.0);
		cam->viewport_height = 2.0 * h; // 뷰포트 높이
		cam->viewport_width = cam->viewport_height * scene->canvas.aspect_ratio;
		// 카메라 좌표계 설정. 기저벡터?
		cam->vup = vector_init(0, 1, 0); // 카메라 기울기
		cam->w = vunit(vmul_t(-1, cam->dir));	// 카메라 좌표계 z축. 카메라와 뷰포트의 거리 단위 벡터
		// cam->w = vunit(vmul_t(h, cam->orig));	// 카메라 좌표계 z축. 카메라와 뷰포트의 거리 단위 벡터
		cam->u = vunit(vcross(cam->vup, cam->w)); // 카메라 좌표계 x축. vup과 w의 외적 : vup 벡터와 w 벡터의 수직 벡터를 카메라 좌표계의 x축으로 잡는다.
		cam->v = vcross(cam->w, cam->u);	// 카메라 좌표계 y축. w와 u의 외적 : w 벡터와 u 벡터의 수직 벡터를 카메라 좌표계의 y축으로 잡는다.
		cam->horizontal = vmul_t(cam->viewport_width, cam->u); // x축 벡터 좌표에 따라 뷰포트 수평 길이 벡터 결정
		cam->vertical = vmul_t(cam->viewport_height, cam->v); // y축 벡터 좌표에 따라 뷰포트 수직 길이 벡터 결정

		// 왼쪽 아래 코너점 좌표. origin - (horiziontal / 2) - (vertical / 2) - w(카메라 좌표계의 z축)
		cam->lower_left_corner = vsub(vsub(vsub(cam->orig, vdiv(cam->horizontal, 2)), vdiv(cam->vertical, 2)), cam->w);
		lst_cam = lst_cam->next;
	}
	// if (scene->camera.fov != fov)
	// 	scene->camera.fov = fov;
	 // 뷰포트 너비
	// scene->camera.focal_length = 1.0; // 카메라와 뷰포트 간의 거리. 초점 거리
	// scene->camera.horizontal = vector_init(scene->camera.viewport_width, 0, 0); // 뷰포트 수평(너비) 길이 벡터
	// scene->camera.vertical = vector_init(0, scene->camera.viewport_height, 0); // 뷰포트 수직(높이) 길이 벡터


	// cam = scene->camera->content;
	// printf("Camera Info (%d)\n", ft_lstsize(scene->camera));
	// printf("Camera View point : %f, %f, %f\n", cam->orig.x, cam->orig.y, cam->orig.z);
	// printf("Camera Direction : %f, %f, %f\n", cam->dir.x, cam->dir.y, cam->dir.z);
	// printf("Camera FOV : %d\n", cam->fov);
	// printf("Camera View up : %f, %f, %f\n", cam->vup.x, cam->vup.y, cam->vup.z);
	// printf("Camera w : %f, %f, %f\n", cam->w.x, cam->w.y, cam->w.z);
	// printf("Camera u : %f, %f, %f\n", cam->u.x, cam->u.y, cam->u.z);
	// printf("Camera v : %f, %f, %f\n", cam->v.x, cam->v.y, cam->v.z);
	// printf("Camera horizontal : %f, %f, %f\n", cam->horizontal.x, cam->horizontal.y, cam->horizontal.z);
	// printf("Camera vertical : %f, %f, %f\n", cam->vertical.x, cam->vertical.y, cam->vertical.z);
	// printf("Lower left Corner Point: %f, %f, %f\n\n", cam->lower_left_corner.x, cam->lower_left_corner.y, cam->lower_left_corner.z);
}

void	set_camera(t_scene *scene)
{
	t_camera	*cam;
	double 		view_angle;
	double 		h;

	cam = scene->camera->content;
	view_angle = cam->fov * MINIRT_PI / 180.0; // 시야각
	h = tan(view_angle / 2.0);
	cam->viewport_height = 2.0 * h; // 뷰포트 높이
	cam->viewport_width = cam->viewport_height * scene->canvas.aspect_ratio;
	// 카메라 좌표계 설정. 기저벡터?
	cam->vup = vector_init(0, 1, 0); // 카메라 기울기
	cam->w = vunit(vmul_t(-1.0, cam->dir));	// 카메라 좌표계 z축. 카메라와 뷰포트의 거리 단위 벡터
	// cam->w = vunit(vmul_t(h, cam->orig));	// 카메라 좌표계 z축. 카메라와 뷰포트의 거리 단위 벡터
	cam->u = vunit(vcross(cam->vup, cam->w)); // 카메라 좌표계 x축. vup과 w의 외적 : vup 벡터와 w 벡터의 수직 벡터를 카메라 좌표계의 x축으로 잡는다.
	cam->v = vcross(cam->w, cam->u);	// 카메라 좌표계 y축. w와 u의 외적 : w 벡터와 u 벡터의 수직 벡터를 카메라 좌표계의 y축으로 잡는다.
	cam->horizontal = vmul_t(cam->viewport_width, cam->u); // x축 벡터 좌표에 따라 뷰포트 수평 길이 벡터 결정
	cam->vertical = vmul_t(cam->viewport_height, cam->v); // y축 벡터 좌표에 따라 뷰포트 수직 길이 벡터 결정

	// 왼쪽 아래 코너점 좌표. origin - (horiziontal / 2) - (vertical / 2) - w(카메라 좌표계의 z축)
	cam->lower_left_corner = vsub(vsub(vsub(cam->orig, vdiv(cam->horizontal, 2)), vdiv(cam->vertical, 2)), cam->w);
	// printf("Camera Info (%d)\n", ft_lstsize(scene->camera));
	// printf("Camera View point : %f, %f, %f\n", cam->orig.x, cam->orig.y, cam->orig.z);
	// printf("Camera Direction : %f, %f, %f\n", cam->dir.x, cam->dir.y, cam->dir.z);
	// printf("Camera FOV : %d\n", cam->fov);
	// printf("Camera View up : %f, %f, %f\n", cam->vup.x, cam->vup.y, cam->vup.z);
	// printf("Camera w : %f, %f, %f\n", cam->w.x, cam->w.y, cam->w.z);
	// printf("Camera u : %f, %f, %f\n", cam->u.x, cam->u.y, cam->u.z);
	// printf("Camera v : %f, %f, %f\n", cam->v.x, cam->v.y, cam->v.z);
	// printf("Camera horizontal : %f, %f, %f\n", cam->horizontal.x, cam->horizontal.y, cam->horizontal.z);
	// printf("Camera vertical : %f, %f, %f\n", cam->vertical.x, cam->vertical.y, cam->vertical.z);
	// printf("Lower left Corner Point: %f, %f, %f\n\n", cam->lower_left_corner.x, cam->lower_left_corner.y, cam->lower_left_corner.z);
}
