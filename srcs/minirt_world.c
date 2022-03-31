/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 13:17:09 by bahn              #+#    #+#             */
/*   Updated: 2022/03/31 16:20:20 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	minirt_world(t_scene *scene)
{
	int			w;
	int			h;
	double		u;
	double		v;
	// t_object	*world;
	
	// world = object_init(SPHERE, sphere_init(point_init(0, 1, -7.5), 2), color_init(1, 1, 1), color_init(1, 1, 1));
	// world = object_init(PLANE, plane_init(point_init(0, -1, -10), vector_init(0, 0, 1)), color_init(1, 1, 1));
	// world = object_init(CYLINDER, cylinder_init(point_init(50.0, 0.0, 20.6), vector_init(0, 0, 1)));
	// object_add(&world, object_init(SQUARE, square_init(point_init(-4, 0, -7), vector_init(1, 0, 0), 2.0), color_init(0, 0, 0)));
	// object_add(&world, object_init(SQUARE, square_init(point_init(4, 0, -7), vector_init(1, 0, 0), 2.0), color_init(0, 0, 0)));
	
	// object_add(&world, object_init(SPHERE, sphere_init(point_init(2, 0, -5), 2)));
	// object_add(&world, object_init(SPHERE, sphere_init(point_init(0, -1000, 0), 999), color_init(0, 0, 0), color_init(1, 1, 1)));

	// object_add(&world, object_init(PLANE, plane_init(point_init(0, 0, -1), vector_init(0, 0, 1)), color_init(0, 0, 0)));
	h = scene->canvas.height - 1;
	while (h >= 0)
	{
		// printf("\rScanlines remaining: %d \n", h); // usleep(5000);
		w = 0;
		while (w < scene->canvas.width)
		{
			u = (double)w / (scene->canvas.width - 1);
			v = (double)h / (scene->canvas.height - 1);
			scene->ray = ray_primary(&scene->camera, u, v);
			minirt_pixel_put_vector(scene->vars->img_data, w, scene->canvas.height - 1 - h, write_color(scene->fd, ray_color(scene->objects, &scene->ray)));
			w++;
		}
		h--;
	}
	mlx_put_image_to_window(scene->vars->mlx, scene->vars->win, scene->vars->img_data->img, 0, 0);
	object_clear(&scene->objects);
}