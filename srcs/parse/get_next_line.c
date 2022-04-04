/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseol <jseol@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 18:17:22 by jseol             #+#    #+#             */
/*   Updated: 2021/11/07 15:04:08 by jseol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	ft_strchr_index(char *s, char c)
{
	int	i;

	i = 0;
	if (s == 0)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static int	ft_newline_line(char **store, size_t index, char **line)
{
	size_t	len;
	char	*tmp;

	(*store)[index] = '\0';
	*line = ft_gnl_strdup(*store);
	len = ft_gnl_strlen(*store + index + 1);
	if (len == 0)
	{
		free(*store);
		*store = 0;
		return (1);
	}
	tmp = ft_gnl_strdup(*store + index + 1);
	free(*store);
	*store = tmp;
	return (1);
}

static int	ft_eof_line(char **store, char **line, int read_size)
{
	int	index;

	index = ft_strchr_index(*store, '\n');
	if (read_size < 0)
		return (-1);
	if (*store && index >= 0)
		return (ft_newline_line(store, index, line));
	else if (*store)
	{
		*line = *store;
		*store = 0;
		return (0);
	}
	*line = ft_gnl_strdup("");
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*store[OPEN_MAX];
	char		buf[BUFFER_SIZE + 1];
	int			read_size;
	int			index;

	if (fd < 0 || line == 0 || BUFFER_SIZE < 1 || fd > OPEN_MAX)
		return (-1);
	read_size = read(fd, buf, BUFFER_SIZE);
	while (read_size > 0)
	{
		buf[read_size] = '\0';
		store[fd] = ft_gnl_strjoin(store[fd], buf);
		index = ft_strchr_index(store[fd], '\n');
		if (index >= 0)
			return (ft_newline_line(&store[fd], index, line));
		read_size = read(fd, buf, BUFFER_SIZE);
	}
	return (ft_eof_line(&store[fd], line, read_size));
}
