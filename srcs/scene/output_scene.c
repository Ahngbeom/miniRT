/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 13:17:09 by bahn              #+#    #+#             */
/*   Updated: 2022/04/25 14:08:13 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

unsigned int	ft_rand(void)
{
	static	unsigned int 	g_bit;
	static	unsigned short	g_lfsr = 0xACE1u;

	g_bit = ((g_lfsr >> 0) ^ (g_lfsr >> 2) ^ (g_lfsr >> 3)
			^ (g_lfsr >> 5)) & 1;
	return (g_lfsr = (g_lfsr >> 1) | (g_bit << 15));
}

double			ft_random_double(void)
{
	return (ft_rand() / (65535 + 1.0));
}

double			ft_random_double_range(double min, double max)
{
	return (min + (max - min) * ft_random_double());
}

void	output_scene(t_scene *scene)
{
	int			w;
	int			h;
	double		u;
	double		v;

	h = scene->canvas.height - 1;
	while (h >= 0)
	{
		w = 0;
		while (w < scene->canvas.width)
		{
			u = (double)w / (scene->canvas.width);
			v = (double)h / (scene->canvas.height);
			// u = ((double)w + ft_random_double()) / (scene->canvas.width);
			// v = ((double)h + ft_random_double()) / (scene->canvas.height);
			scene->ray = ray_primary(scene->camera->content, u, v);
			minirt_pixel_put_vector(scene->vars->img_data, w, scene->canvas.height - 1 - h, write_color(ray_color(scene)));
			w++;
		}
		h--;
	}
	mlx_put_image_to_window(scene->vars->mlx, scene->vars->win, scene->vars->img_data->img, 0, 0);
}