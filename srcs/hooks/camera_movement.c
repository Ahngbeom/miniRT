/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:24:38 by bahn              #+#    #+#             */
/*   Updated: 2022/03/30 17:07:31 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	camera_move(int keycode, t_minirt *minirt)
{
	printf("keycode : %d\n", keycode);
	if (keycode == 65362)
		minirt->camera->orig.y += 0.1;
	else if (keycode == 65364)
		minirt->camera->orig.y -= 0.1;
	else if (keycode == 65361)
		minirt->camera->orig.x -= 0.1;
	else if (keycode == 65363)
		minirt->camera->orig.x += 0.1;
	else
		return (0);
	
	minirt->camera->lower_left_corner = vsub(vsub(vsub(minirt->camera->orig, vdiv(minirt->camera->horizontal, 2)), vdiv(minirt->camera->vertical, 2)), vector_init(0, 0, minirt->camera->focal_length));
	
	minirt_world(minirt);
	
	printf("Camera Info\n");
	printf("Origin : %f, %f, %f\n", minirt->camera->orig.x, minirt->camera->orig.y, minirt->camera->orig.z);
	printf("Focal Length : %f\n", minirt->camera->focal_length);
	printf("Lower left Corner Point: %f, %f, %f\n", minirt->camera->lower_left_corner.x, minirt->camera->lower_left_corner.y, minirt->camera->lower_left_corner.z);
	return (0);
}

int	camera_zoom(int keycode, int x, int y, t_minirt *minirt)
{
	printf("mouse keycode : %d (%d, %d)\n", keycode, x, y);
	if (keycode == 4)
		minirt->camera->focal_length += 0.1;
	else if (keycode == 5)
		minirt->camera->focal_length -= 0.1;
	else
		return (0);
	minirt->camera->lower_left_corner = vsub(vsub(vsub(minirt->camera->orig, vdiv(minirt->camera->horizontal, 2)), vdiv(minirt->camera->vertical, 2)), vector_init(0, 0, minirt->camera->focal_length));
	minirt_world(minirt);
	
	printf("Camera Info\n");
	printf("Origin Point: %f, %f, %f\n", minirt->camera->orig.x, minirt->camera->orig.y, minirt->camera->orig.z);
	printf("Focal Length: %f\n", minirt->camera->focal_length);
	printf("Lower left Corner Point: %f, %f, %f\n", minirt->camera->lower_left_corner.x, minirt->camera->lower_left_corner.y, minirt->camera->lower_left_corner.z);
	return (0);
}