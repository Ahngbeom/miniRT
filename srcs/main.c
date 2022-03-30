/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:54:42 by bahn              #+#    #+#             */
/*   Updated: 2022/03/30 13:32:29 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	minirt_init(t_minirt *minirt, int argc, char const *argv[])
{
	minirt->fd = -1;
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
		minirt->fd = open(argv[1], O_CREAT | O_TRUNC | O_RDWR, 00777);
		if (minirt->fd == -1)
		{
			printf("Invalid File path or File\n");
			exit(1);
		}
		else
		{
			ft_putendl_fd("P3", minirt->fd);
			ft_putnbr_fd(WIDTH, minirt->fd);
			ft_putchar_fd(' ', minirt->fd);
			ft_putnbr_fd(HEIGHT, minirt->fd);
			ft_putchar_fd('\n', minirt->fd);
			ft_putendl_fd("255", minirt->fd);
		}
	}
	minirt->vars = ft_calloc(sizeof(t_vars), 1);
	minirt->vars->mlx = mlx_init();
	minirt->vars->win = mlx_new_window(minirt->vars->mlx, WIDTH, HEIGHT, "minirt");
	
	minirt->img_data = ft_calloc(sizeof(t_img_data), 1);
	minirt->img_data->img = mlx_new_image(minirt->vars->mlx, WIDTH, HEIGHT);
	minirt->img_data->addr = mlx_get_data_addr(minirt->img_data->img, \
												&minirt->img_data->bits_per_pixel, \
												&minirt->img_data->line_length, \
												&minirt->img_data->endian);
	
	canvas_init(minirt, WIDTH, HEIGHT);
	camera_init(minirt, minirt->canvas, vector_init(0, 0, 0));
	
	minirt->ray = ft_calloc(sizeof(t_ray), 1);
}

int main(int argc, char const *argv[])
{
	t_minirt	minirt;

	minirt_init(&minirt, argc, argv);
	
	// minirt_background(minirt.img_data, WIDTH, HEIGHT, vector_init(255, 255, 0));
	// minirt_gradation(&minirt);
	// minirt_sky(&minirt);
	minirt_world(&minirt);

	mlx_hook(minirt.vars->win, 2, 1L << 0, minirt_esc, &minirt);
	mlx_hook(minirt.vars->win, 17, 1L << 2, minirt_close, &minirt);

	mlx_key_hook(minirt.vars->win, camera_move, &minirt);
	mlx_mouse_hook(minirt.vars->win, camera_zoom, &minirt);

	mlx_loop(minirt.vars->mlx);
	// mlx_loop_end(minirt.vars->mlx);
	
	return 0;
}
