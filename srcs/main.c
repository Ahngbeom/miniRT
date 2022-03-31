/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:54:42 by bahn              #+#    #+#             */
/*   Updated: 2022/03/31 16:19:51 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	scene_init(t_scene *scene, int argc, char const *argv[])
{
	scene->fd = -1;
	if (argc == 2 || argc > 3)
	{
		printf("Invalid Arguments\n");
		printf("./miniRT\n");
		printf("./miniRT [file path to save] [--save]\n");
		printf("./miniRT [.rt file path] [--save]\n");
		exit(1);
	}
	else if (argc == 3)
	{
		if (ft_strncmp((char*)argv[2], "--save", 6))
		{
			printf("Invalid Arguments\n");
			printf("./miniRT\n");
			printf("./miniRT [file path to save] [--save]\n");
			printf("./miniRT [.rt file path] [--save]\n");
			exit(1);
		}
		scene->fd = open(argv[1], O_CREAT | O_TRUNC | O_RDWR, 00777);
		if (scene->fd == -1)
		{
			printf("Invalid File path or File\n");
			exit(1);
		}
		else
		{
			ft_putendl_fd("P3", scene->fd);
			ft_putnbr_fd(WIDTH, scene->fd);
			ft_putchar_fd(' ', scene->fd);
			ft_putnbr_fd(HEIGHT, scene->fd);
			ft_putchar_fd('\n', scene->fd);
			ft_putendl_fd("255", scene->fd);
		}
	}
	scene->vars = ft_calloc(sizeof(t_vars), 1);
	scene->vars->mlx = mlx_init();
	scene->vars->win = mlx_new_window(scene->vars->mlx, WIDTH, HEIGHT, "scene");
	
	scene->vars->img_data = ft_calloc(sizeof(t_img_data), 1);
	scene->vars->img_data->img = mlx_new_image(scene->vars->mlx, WIDTH, HEIGHT);
	scene->vars->img_data->addr = mlx_get_data_addr(scene->vars->img_data->img, \
												&scene->vars->img_data->bits_per_pixel, \
												&scene->vars->img_data->line_length, \
												&scene->vars->img_data->endian);
												
	canvas_init(scene, WIDTH, HEIGHT);
	camera_init(scene, vector_init(0, 0, 0));
	
	// scene->ray = ft_calloc(sizeof(t_ray), 1);
}

int main(int argc, char const *argv[])
{
	t_scene	scene;

	scene_init(&scene, argc, argv);
	
	// minirt_background(scene.img_data, WIDTH, HEIGHT, vector_init(255, 255, 0));
	// minirt_gradation(&scene);
	// minirt_sky(&scene);
	minirt_world(&scene);

	mlx_hook(scene.vars->win, 2, 1L << 0, minirt_esc, &scene);
	mlx_hook(scene.vars->win, 17, 1L << 2, minirt_close, &scene);

	mlx_key_hook(scene.vars->win, camera_move, &scene);
	mlx_mouse_hook(scene.vars->win, camera_zoom, &scene);

	mlx_loop(scene.vars->mlx);
	// mlx_loop_end(scene.vars->mlx);
	return 0;
}
