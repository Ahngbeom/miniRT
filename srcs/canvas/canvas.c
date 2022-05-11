/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseol <jseol@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:07:21 by bahn              #+#    #+#             */
/*   Updated: 2022/05/04 17:13:43 by jseol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_canvas(t_scene *scene, int width, int height)
{
	scene->canvas.width = width;
	scene->canvas.height = height;
	scene->canvas.aspect_ratio = (double)width / (double)height;
}
