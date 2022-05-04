/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseol <jseol@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:52:11 by jaeyu             #+#    #+#             */
/*   Updated: 2022/05/04 19:07:45 by jseol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_error(char *s)
{
	printf("Error\n");
	printf("%s\n", s);
	exit(1);
}

int	allowed_symbol(char c)
{
	if (c == '\t' || c == ' ' || c == '\n' || c == '.' || c == ',' || \
		(c >= '0' && c <= '9') || c == '-')
		return (1);
	return (0);
}

int	check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!allowed_symbol(line[i]) && i > 1)
			return (0);
		i++;
	}
	return (1);
}

void	parse_line(t_scene *scene, char **split)
{
	if (split_size(split) == 0)
		return ;
	else if (split_size(split) < 3)
		print_error("Unknown element in the scene");
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
		print_error("Unknown element in the scene");
}

void	parse_file(t_scene *scene, const char *filename)
{
	int		fd;
	int		ret;
	char	*line;
	char	**split;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_error("Not found file");
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		split = ft_split2(line, ' ', '\t');
		if (!check_line(line))
			print_error("Forbidden symbol in the scene");
		parse_line(scene, split);
		free(line);
		split_free(split);
	}
	ret = get_next_line(fd, &line);
	split = ft_split2(line, ' ', '\t');
	parse_line(scene, split);
	free(line);
	split_free(split);
	close(fd);
}
