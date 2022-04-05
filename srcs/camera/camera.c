/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyu <jaeyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:11:41 by bahn              #+#    #+#             */
/*   Updated: 2022/04/05 19:30:23 by jaeyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	camera_init(t_scene *scene)
{
	// orig (coordinates of the view point)
	// normal (normalized orientation vector)
	// fov (Horizontal field of view)
	
	scene->camera.viewport_height = 2.0; // 뷰포트 높이
	scene->camera.viewport_width = scene->camera.viewport_height * scene->canvas.aspect_ratio; // 뷰포트 너비
	scene->camera.focal_length = 1.0; // 카메라와 뷰포트 간의 거리. 초점 거리
	scene->camera.horizontal = vector_init(scene->camera.viewport_width, 0, 0); // 뷰포트 수평(너비) 길이 벡터
	scene->camera.vertical = vector_init(0, scene->camera.viewport_height, 0); // 뷰포트 수직(높이) 길이 벡터
	
	// 왼쪽 아래 코너점 좌표. origin - (horiziontal / 2) - (vertical / 2) - vecter(0, 0, focal_length)
	scene->camera.lower_left_corner = vsub(vsub(vsub(scene->camera.orig, vdiv(scene->camera.horizontal, 2)), vdiv(scene->camera.vertical, 2)), vector_init(0, 0, scene->camera.focal_length));
}

void	init_camera(t_scene *scene, int fov)
{
	double	view_angle;
	double	h;

	view_angle = fov * MINIRT_PI / 180.0; // 시야각
	h = tan(view_angle / 2.0);
	printf("%f\n", view_angle);
	printf("%f\n", h);
	scene->camera.viewport_height = 2.0 * h; // 뷰포트 높이
	scene->camera.viewport_width = scene->camera.viewport_height * scene->canvas.aspect_ratio; // 뷰포트 너비
	scene->camera.focal_length = 1.0; // 카메라와 뷰포트 간의 거리. 초점 거리
	scene->camera.horizontal = vector_init(scene->camera.viewport_width, 0, 0); // 뷰포트 수평(너비) 길이 벡터
	scene->camera.vertical = vector_init(0, scene->camera.viewport_height, 0); // 뷰포트 수직(높이) 길이 벡터

	// 추가
	scene->camera.vup = vector_init(0, 1, 0);
	scene->camera.w = vunit(vmul_t(-1, scene->camera.dir));		// !!!
	scene->camera.u = vunit(vcross(scene->camera.vup, scene->camera.w));
	scene->camera.v = vcross(scene->camera.w, scene->camera.u);
	scene->camera.horizontal = vmul_t(scene->camera.viewport_width, scene->camera.u);
	scene->camera.vertical = vmul_t(scene->camera.viewport_height, scene->camera.v);


	// 왼쪽 아래 코너점 좌표. origin - (horiziontal / 2) - (vertical / 2) - vecter(0, 0, focal_length)
	scene->camera.lower_left_corner = vsub(vsub(vsub(scene->camera.orig, vdiv(scene->camera.horizontal, 2)), vdiv(scene->camera.vertical, 2)), vector_init(0, 0, scene->camera.focal_length));
}