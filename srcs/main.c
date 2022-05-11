/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseol <jseol@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:54:42 by bahn              #+#    #+#             */
/*   Updated: 2022/05/11 13:12:23 by jseol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	check_rtfile(const char *filename)
{
	char	**split;
	int		cnt;

	split = ft_split(filename, '.');
	cnt = split_size(split);
	if (cnt != 2)
		print_error("Invalid filename [*.rt]");
	if (ft_strcmp(split[0], "") == 0 || ft_strcmp(split[1], "rt") != 0)
		print_error("Invalid filename [*.rt]");
	split_free(split);
}

static void	init_scene(t_scene *scene, int argc, char const *argv[])
{
	if (argc != 2)
		print_error("Invalid Arguments\n./miniRT\n");
	scene->camera = NULL;
	scene->lights = NULL;
	scene->objects = NULL;
	check_rtfile(argv[1]);
	parse_file(scene, argv[1]);
	scene->vars = ft_calloc(sizeof(t_vars), 1);
	scene->vars->mlx = mlx_init();
	scene->vars->win = mlx_new_window(scene->vars->mlx, WIDTH, HEIGHT, \
									"miniRT");
	scene->vars->img_data = ft_calloc(sizeof(t_img_data), 1);
	scene->vars->img_data->img = mlx_new_image(scene->vars->mlx, WIDTH, HEIGHT);
	scene->vars->img_data->addr = mlx_get_data_addr(scene->vars->img_data->img, \
									&scene->vars->img_data->bits_per_pixel, \
									&scene->vars->img_data->line_length, \
									&scene->vars->img_data->endian);
	init_canvas(scene, WIDTH, HEIGHT);
	init_camera(scene);
}

int	main(int argc, char const *argv[])
{
	t_scene		scene;

	init_scene(&scene, argc, argv);
	output_scene(&scene);
	mlx_hook(scene.vars->win, 2, 1L << 0, minirt_esc, &scene);
	mlx_hook(scene.vars->win, 17, 1L << 2, minirt_close, &scene);
	mlx_key_hook(scene.vars->win, camera_move, &scene);
	mlx_mouse_hook(scene.vars->win, camera_zoom, &scene);
	mlx_loop(scene.vars->mlx);
	return (0);
}
