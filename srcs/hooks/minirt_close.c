/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_close.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:17:00 by bahn              #+#    #+#             */
/*   Updated: 2022/03/29 20:58:48 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	minirt_close(int keycode, t_minirt *miniRT)
{
	(void)keycode;
	if (miniRT != NULL)
	{
		mlx_destroy_image(miniRT->vars->mlx, miniRT->img_data->img);
		mlx_destroy_window(miniRT->vars->mlx, miniRT->vars->win);
		minirt_free(miniRT->vars->mlx);
		minirt_free(miniRT->vars);
		minirt_free(miniRT->img_data);
		minirt_free(miniRT->ray);
		minirt_free(miniRT->canvas);
		minirt_free(miniRT->camera);
	}
	// system("leaks --exclude --atExit miniRT");
	exit(0);
	return (0);
}