/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 02:51:10 by bahn              #+#    #+#             */
/*   Updated: 2022/05/05 00:52:03 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	minirt_pixel_put_vector(t_img_data *data, int x, int y, t_color3 color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = (int)(color.x) << 16 | (int)(color.y) << 8 \
														| (int)(color.z);
}

t_color3	write_color(t_color3 color)
{
	return (vector_init(255.999 * color.x, 255.999 * color.y, \
											255.999 * color.z));
}

t_color3	skyview_by_ray(t_ray *ray)
{
	double		t;
	t_color3	t_color;
	t_color3	t_skyblue;

	t = 0.5 * (ray->dir.y + 1.0);
	t_color = vmul_t(1.0 - t, vector_init(1.0, 1.0, 1.0));
	t_skyblue = vmul_t(t, vector_init(0.5, 0.7, 1.0));
	return (vsum(t_color, t_skyblue));
}
