/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:07:21 by bahn              #+#    #+#             */
/*   Updated: 2022/03/31 15:49:31 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	canvas_init(t_scene *scene, int width, int height)
{
	// scene->canvas = ft_calloc(sizeof(t_canvas), 1);
	
	scene->canvas.width = width;
	scene->canvas.height = height;
	scene->canvas.aspect_ratio = (double)width / (double)height;
}