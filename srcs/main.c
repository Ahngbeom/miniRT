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
	if (argc > 3)
	{
		printf("Invalid Arguments\n");
		printf("./miniRT\n");
		printf("./miniRT [file path to save] [--save]\n");
		printf("./miniRT [.rt file path] [--save]\n");
		exit(1);
	}
	else if (argc >= 2)
	{
		if (argc == 3 && ft_strncmp((char*)argv[2], "--save", 6))
		{
			printf("Invalid Arguments\n");
			printf("./miniRT\n");
			printf("./miniRT [file path to save] [--save]\n");
			printf("./miniRT [.rt file path] [--save]\n");
			exit(1);
		}
		scene->objects = NULL;
		parse_file(scene, argv[1]);
		// scene->fd = open(argv[1], O_CREAT | O_TRUNC | O_RDWR, 00777);
		// if (scene->fd == -1)
		// {
		// 	printf("Invalid File path or File\n");
		// 	exit(1);
		// }
		// else
		// {
		// 	ft_putendl_fd("P3", scene->fd);
		// 	ft_putnbr_fd(WIDTH, scene->fd);
		// 	ft_putchar_fd(' ', scene->fd);
		// 	ft_putnbr_fd(HEIGHT, scene->fd);
		// 	ft_putchar_fd('\n', scene->fd);
		// 	ft_putendl_fd("255", scene->fd);
		// }
	}
	else
	{
		printf("Error\n");
		exit(1);
	}
	scene->vars = ft_calloc(sizeof(t_vars), 1);
	scene->vars->mlx = mlx_init();
	scene->vars->win = mlx_new_window(scene->vars->mlx, WIDTH, HEIGHT, "miniRT");
	
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
	t_scene		scene;
	
	scene_init(&scene, argc, argv);
	
	printf("Ambient Ratio : %f\n", scene.ambient.ratio);
	printf("Ambient Color : %f, %f, %f\n\n", scene.ambient.color.x, scene.ambient.color.y, scene.ambient.color.z);

	printf("Camera Viewpoint : %f, %f, %f\n", scene.camera.orig.x, scene.camera.orig.y, scene.camera.orig.z);
	printf("Camera Direction : %f, %f, %f\n", scene.camera.dir.x, scene.camera.dir.y, scene.camera.dir.z);
	printf("Camera FOV : %d\n\n", scene.camera.fov);

	printf("Light Point : %f, %f, %f\n", scene.light.orig.x, scene.light.orig.y, scene.light.orig.z);
	printf("Light Ratio : %f\n", scene.light.bright_ratio);
	printf("Light Color : %f, %f, %f\n\n", scene.light.light_color.x, scene.light.light_color.y, scene.light.light_color.z);
	
	t_object *list = scene.objects;
	while (list != NULL)
	{
		if (list->type == SPHERE)
		{
			printf("Type : SPHERE(%d)\n", list->type);
			printf("Center : %f, %f, %f\n", ((t_sphere*)list->element)->center.x, ((t_sphere*)list->element)->center.y, ((t_sphere*)list->element)->center.z);
			printf("Diameter : %f\n", ((t_sphere*)list->element)->diameter);
			printf("Color : %f, %f, %f\n\n", list->color.x, list->color.y, list->color.z);
		}
		else if (list->type == PLANE)
		{
			printf("Type : PLANE(%d)\n", list->type);
			printf("Coodinates : %f, %f, %f\n", ((t_plane*)list->element)->coord.x, ((t_plane*)list->element)->coord.y, ((t_plane*)list->element)->coord.z);
			printf("Normal Vector : %f, %f, %f\n", ((t_plane*)list->element)->normal.x, ((t_plane*)list->element)->normal.y, ((t_plane*)list->element)->normal.z);
			printf("Color : %f, %f, %f\n\n", list->color.x, list->color.y, list->color.z);
		}
		else if(list->type == CYLINDER)
		{
			printf("Type : CYLINDER(%d)\n", list->type);
			printf("Coodinates : %f, %f, %f\n", ((t_cylinder*)list->element)->coord.x, ((t_cylinder*)list->element)->coord.y, ((t_cylinder*)list->element)->coord.z);
			printf("Normal Vector : %f, %f, %f\n", ((t_cylinder*)list->element)->normal.x, ((t_cylinder*)list->element)->normal.y, ((t_cylinder*)list->element)->normal.z);
			printf("Diameter : %f\n", ((t_cylinder*)list->element)->diameter);
			printf("Height : %f\n", ((t_cylinder*)list->element)->height);
			printf("Color : %f, %f, %f\n\n", list->color.x, list->color.y, list->color.z);
		}
		list = list->next;
	}
	// exit(0);
	
	
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
