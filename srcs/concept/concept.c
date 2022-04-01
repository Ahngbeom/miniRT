/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concept.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:47:54 by bahn              #+#    #+#             */
/*   Updated: 2022/03/31 16:19:34 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	minirt_background(t_img_data *data, int width, int height, t_vec3 color)
{
	int	w;
	int	h;
	
	printf("P3\n%d %d\n255\n", width, height);
	w = -1;
	while (++w < width)
	{
		h = -1;
		while(++h < height)
		{
			printf("%d %d %d\n", ((int)color.x), ((int)color.y), (int)color.z);
			minirt_pixel_put_vector(data, w, h, color);
		}
	}
}

void	minirt_gradation(t_scene *scene)
{
	t_vec3	rgb;
	int		w;
	int		h;
	
	printf("P3\n%d %d\n255\n", scene->canvas.width, scene->canvas.height);
	h = scene->canvas.height - 1;
	while (h >= 0)
	{
		w = 0;
		while (w < scene->canvas.width)
		{
			rgb.x = (double)w / (scene->canvas.width - 1);
			rgb.y = (double)h / (scene->canvas.height - 1);
			rgb.z = 0.25;
			minirt_pixel_put_vector(scene->vars->img_data, w, scene->canvas.height - 1 - h, \
										write_color(scene->fd, color_init(rgb.x, rgb.y, rgb.z)));
			w++;
		}
		h--;
	}
}

void	minirt_sky(t_scene	*scene)
{
	int		w;
	int		h;
	double	u;
	double	v;
	t_ray	ray;

	printf("P3\n%d %d\n255\n", scene->canvas.width, scene->canvas.height);

	h = scene->canvas.height - 1;
	while (h >= 0)
	{
		printf("\rScanlines remaining: %d ", h); // usleep(5000);
		w = 0;
		while (w < scene->canvas.width)
		{
			u = (double)w / (scene->canvas.width - 1);		
			v = (double)h / (scene->canvas.height - 1);	
			ray = ray_primary(&scene->camera, u, v);
			minirt_pixel_put_vector(scene->vars->img_data, w, (scene->canvas.height - 1) - h, \
										write_color(scene->fd, ray_color(NULL, &ray)));
			w++;
		}
		h--;
	}
}

// void	minirt_plane_in_the_sky(t_scene *scene)
// {
// 	int			w;
// 	int			h;
// 	double		u;
// 	double		v;
// 	t_plane		plane;

// 	printf("P3\n%d %d\n255\n", scene->canvas.width, scene->canvas.height);
// 	h = scene->canvas.height - 1;
// 	plane = plane_init(vector_init(0.0, 0.0, -5.0), vector_init(0.0, 0.0, -1.0));
// 	while (h >= 0)
// 	{
// 		printf("\rScanlines remaining: %d ", h); // usleep(5000);
// 		w = 0;
// 		while (w < scene->canvas.width)
// 		{
// 			u = (double)w / (scene->canvas.width - 1);
// 			v = (double)h / (scene->canvas.height - 1);
// 			*scene->ray = ray_primary(scene->camera, u, v);
// 			minirt_pixel_put_vector(scene->img_data, w, scene->canvas.height - 1- h, write_color(ray_color(PLANE, &plane, scene->ray)));
// 			w++;
// 		}
// 		h--;
// 	}
// }