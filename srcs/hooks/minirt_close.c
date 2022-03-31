/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_close.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:17:00 by bahn              #+#    #+#             */
/*   Updated: 2022/03/31 16:26:11 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	minirt_close(int keycode, t_scene *scene)
{
	// (void)scene;
	// if (scene != NULL)
	// {
		// mlx_destroy_image(scene->vars->mlx, scene->vars->img_data->img);
		// mlx_destroy_window(scene->vars->mlx, scene->vars->win);
		// nullcheck_free(scene->vars->mlx);
	// }
	// system("leaks --exclude --atExit scene");
	if (keycode != -1)
		exit(0);
	else
		return (0);
}