/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_close.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:17:00 by bahn              #+#    #+#             */
/*   Updated: 2022/05/05 11:43:43 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	minirt_close(t_scene *scene)
{
	lstclear(&scene->camera);
	lstclear(&scene->lights);
	object_clear(&scene->objects);
	mlx_destroy_image(scene->vars->mlx, scene->vars->img_data->img);
	mlx_destroy_window(scene->vars->mlx, scene->vars->win);
	nullcheck_free(scene->vars->img_data);
	nullcheck_free(scene->vars);
	exit(0);
}
