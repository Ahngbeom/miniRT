/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:11:41 by bahn              #+#    #+#             */
/*   Updated: 2022/03/29 21:01:40 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	camera_init(t_minirt *minirt, t_canvas *canvas, t_point3 origin)
{
	minirt->camera = ft_calloc(sizeof(t_camera), 1);
	if (minirt->camera == NULL)
		minirt_close(0, minirt);
	minirt->camera->orig = origin; // 카메라 원점
	minirt->camera->viewport_height = 2.0; // 뷰포트 높이
	minirt->camera->viewport_width = minirt->camera->viewport_height * canvas->aspect_ratio; // 뷰포트 너비
	minirt->camera->focal_length = 1.0; // 카메라와 뷰포트 간의 거리. 초점 거리
	minirt->camera->horizontal = vector_init(minirt->camera->viewport_width, 0, 0); // 뷰포트 수평(너비) 길이 벡터
	minirt->camera->vertical = vector_init(0, minirt->camera->viewport_height, 0); // 뷰포트 수직(높이) 길이 벡터
	
	// 왼쪽 아래 코너점 좌표. origin - (horiziontal / 2) - (vertical / 2) - vecter(0, 0, focal_length)
	minirt->camera->lower_left_corner = vsub(vsub(vsub(minirt->camera->orig, vdiv(minirt->camera->horizontal, 2)), vdiv(minirt->camera->vertical, 2)), vector_init(0, 0, minirt->camera->focal_length));


	// orig (coordinates of the view point)
	// normal (normalized orientation vector)
	// fov (Horizontal field of view)
}