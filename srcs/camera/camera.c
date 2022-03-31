/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:11:41 by bahn              #+#    #+#             */
/*   Updated: 2022/03/31 15:48:53 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	camera_init(t_scene *scene, t_point3 origin)
{
	// scene->camera = ft_calloc(sizeof(t_camera), 1);
	// if (scene->camera == NULL)
	// 	minirt_close(0, scene);
	scene->camera.orig = origin; // 카메라 원점
	scene->camera.viewport_height = 2.0; // 뷰포트 높이
	scene->camera.viewport_width = scene->camera.viewport_height * scene->canvas.aspect_ratio; // 뷰포트 너비
	scene->camera.focal_length = 1.0; // 카메라와 뷰포트 간의 거리. 초점 거리
	scene->camera.horizontal = vector_init(scene->camera.viewport_width, 0, 0); // 뷰포트 수평(너비) 길이 벡터
	scene->camera.vertical = vector_init(0, scene->camera.viewport_height, 0); // 뷰포트 수직(높이) 길이 벡터
	
	// 왼쪽 아래 코너점 좌표. origin - (horiziontal / 2) - (vertical / 2) - vecter(0, 0, focal_length)
	scene->camera.lower_left_corner = vsub(vsub(vsub(scene->camera.orig, vdiv(scene->camera.horizontal, 2)), vdiv(scene->camera.vertical, 2)), vector_init(0, 0, scene->camera.focal_length));


	// orig (coordinates of the view point)
	// normal (normalized orientation vector)
	// fov (Horizontal field of view)
}