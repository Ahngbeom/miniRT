/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyu <jaeyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:25:12 by jaeyu             #+#    #+#             */
/*   Updated: 2022/03/30 19:34:49 by jaeyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		allowed_symbol(char c)
{
	if (c == '\t' | c == ' ' | c == '\n' | c == '.' || c == ',' ||
	(c >= '0' && c <= '9') || c == '-')
		return (1);
	return (0);
}

int		check_line(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (!allowed_symbol(line[i]) && i > 1)
			return (0);
		i++;
	}
	return (1);
}

int		split_size(char **split)
{
	int i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

void	parse_line(t_scene *scene, char **split)
{
	if (split_size(split) == 0)
		return ;
	else if (split_size(split) < 3)
		printf("Error\n");//	구성이 최소 3개
	if (ft_strncmp(split[0], "A", 1) == 0)
		parse_ambient(scene, split);
	else if (ft_strncmp(split[0], "C", 1) == 0)
		parse_camera(scene, split);
	else if (ft_strncmp(split[0], "L", 1) == 0)
		parse_light(scene, split);
	else if (ft_strncmp(split[0], "sp", 2) == 0)
		parse_sphere(scene, split);
	else if (ft_strncmp(split[0], "pl", 2) == 0)
		parse_plane(scene, split);
	else if (ft_strncmp(split[0], "cy", 2) == 0)
		parse_cylinder(scene, split);
	else
		printf("Error\n");// 존재하지 않는
}

void	init_scene(t_scene *scene)
{
	scene->ambient = NULL;
	scene->camera = NULL;
	scene->light = NULL;
	scene->object = NULL;
}

static t_scene	*parse_file(char *filename)
{
	int		fd;
	int		ret;
	char	*line;
	char	**split;
	t_scene	*scene;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	scene = malloc(sizeof(t_scene));
	init_scene(scene);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		split = ft_split(line, ' ');
		if (!check_line(line))
			printf("Error\n");// 에러출력
		parse_line(scene, split);
		free (line);
	}
	split = ft_split(line, ' ');
	parse_line(scene, split);
	free (line);
	close(fd);
	return (scene);
}

static void	minirt(char *filename)
{
	t_scene *scene;

	scene = parse_file(filename);
}

int		main(int argc, char **argv)
{
	if (argc != 2)
		return (1);	// Error
	else
		minirt(argv[1]);
	
	return (0);
}