/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:11:41 by bahn              #+#    #+#             */
/*   Updated: 2022/04/06 00:29:19 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_camera(t_scene *scene, int fov)
{
	double	view_angle;
	double	h;

	if (scene->camera.fov != fov)
		scene->camera.fov = fov;
	view_angle = scene->camera.fov * MINIRT_PI / 180.0; // 시야각
	h = tan(view_angle / 2.0);
	scene->camera.viewport_height = 2.0 * h; // 뷰포트 높이
	scene->camera.viewport_width = scene->camera.viewport_height * scene->canvas.aspect_ratio; // 뷰포트 너비
	// scene->camera.focal_length = 1.0; // 카메라와 뷰포트 간의 거리. 초점 거리
	// scene->camera.horizontal = vector_init(scene->camera.viewport_width, 0, 0); // 뷰포트 수평(너비) 길이 벡터
	// scene->camera.vertical = vector_init(0, scene->camera.viewport_height, 0); // 뷰포트 수직(높이) 길이 벡터

	// 카메라 좌표계 설정. 기저벡터?
	scene->camera.vup = vector_init(0, 1, 0); // 카메라 기울기
	scene->camera.w = vunit(vmul_t(-1.0, scene->camera.dir));	// 카메라 좌표계 z축. 카메라와 뷰포트의 거리 단위 벡터
	scene->camera.u = vunit(vcross(scene->camera.vup, scene->camera.w)); // 카메라 좌표계 x축. vup과 w의 외적 : vup 벡터와 w 벡터의 수직 벡터를 카메라 좌표계의 x축으로 잡는다.
	scene->camera.v = vcross(scene->camera.w, scene->camera.u);	// 카메라 좌표계 y축. w와 u의 외적 : w 벡터와 u 벡터의 수직 벡터를 카메라 좌표계의 y축으로 잡는다.
	scene->camera.horizontal = vmul_t(scene->camera.viewport_width, scene->camera.u); // x축 벡터 좌표에 따라 뷰포트 수평 길이 벡터 결정
	scene->camera.vertical = vmul_t(scene->camera.viewport_height, scene->camera.v); // y축 벡터 좌표에 따라 뷰포트 수직 길이 벡터 결정

	// 왼쪽 아래 코너점 좌표. origin - (horiziontal / 2) - (vertical / 2) - w(카메라 좌표계의 z축)
	scene->camera.lower_left_corner = vsub(vsub(vsub(scene->camera.orig, vdiv(scene->camera.horizontal, 2)), vdiv(scene->camera.vertical, 2)), scene->camera.w);

	printf("Camera Info\n");
	printf("Camera View point : %f, %f, %f\n", scene->camera.orig.x, scene->camera.orig.y, scene->camera.orig.z);
	printf("Camera Direction : %f, %f, %f\n", scene->camera.dir.x, scene->camera.dir.y, scene->camera.dir.z);
	printf("Camera FOV : %d\n", scene->camera.fov);
	printf("Camera View up : %f, %f, %f\n", scene->camera.vup.x, scene->camera.vup.y, scene->camera.vup.z);
	printf("Camera w : %f, %f, %f\n", scene->camera.w.x, scene->camera.w.y, scene->camera.w.z);
	printf("Camera u : %f, %f, %f\n", scene->camera.u.x, scene->camera.u.y, scene->camera.u.z);
	printf("Camera v : %f, %f, %f\n", scene->camera.v.x, scene->camera.v.y, scene->camera.v.z);
	printf("Camera horizontal : %f, %f, %f\n", scene->camera.horizontal.x, scene->camera.horizontal.y, scene->camera.horizontal.z);
	printf("Camera vertical : %f, %f, %f\n", scene->camera.vertical.x, scene->camera.vertical.y, scene->camera.vertical.z);
	printf("Lower left Corner Point: %f, %f, %f\n\n", scene->camera.lower_left_corner.x, scene->camera.lower_left_corner.y, scene->camera.lower_left_corner.z);
}