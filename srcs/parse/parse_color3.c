/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyu <jaeyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:49:39 by jaeyu             #+#    #+#             */
/*   Updated: 2022/03/31 15:04:05 by jaeyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		check_color3(t_color3 rgb)
{
	if (rgb.x < 0 || rgb.x > 255 || rgb.y < 0 || rgb.y > 255 || rgb.z < 0 ||
	rgb.z > 255)
		return (0);
	return (1);
}

void	parse_color3(t_color3 *ret, char *color)
{
	char **split;
	int		i;

	split = ft_split(color, ',');
	if (split_size(split) != 3)
		printf("Color format: R,G,B");
	ret->x = (double)ft_atoi(split[0]);
	ret->y = (double)ft_atoi(split[1]);
	ret->z = (double)ft_atoi(split[2]);
	i = -1;
	while (split[++i] != NULL)
		free(split[i]);
	free(split);
}