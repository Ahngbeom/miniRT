/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:07:21 by bahn              #+#    #+#             */
/*   Updated: 2022/03/29 21:02:26 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	canvas_init(t_minirt *minirt, int width, int height)
{
	minirt->canvas = ft_calloc(sizeof(t_canvas), 1);
	
	minirt->canvas->width = width;
	minirt->canvas->height = height;
	minirt->canvas->aspect_ratio = (double)width / (double)height;
}