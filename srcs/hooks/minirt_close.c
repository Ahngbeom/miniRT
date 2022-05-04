/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_close.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseol <jseol@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:17:00 by bahn              #+#    #+#             */
/*   Updated: 2022/05/04 15:59:25 by jseol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	minirt_close(int keycode, t_scene *scene)
{
	(void)scene;
	// if (scene != NULL)
	// {
		// mlx_destroy_image(scene->vars->mlx, scene->vars->img_data->img);
		// mlx_destroy_window(scene->vars->mlx, scene->vars->win);
		// nullcheck_free(scene->vars->mlx);
	// }
	// system("leaks miniRT");
	if (keycode != -1) {
		lstclear(&scene->camera);
		lstclear(&scene->lights);
		object_clear(&scene->objects);
		mlx_destroy_image(scene->vars->mlx, scene->vars->img_data->img);
		mlx_destroy_window(scene->vars->mlx, scene->vars->win);
		nullcheck_free(scene->vars->img_data);
		nullcheck_free(scene->vars);
		system("leaks miniRT");
		exit(0);
	}
	else
		return (0);
}
