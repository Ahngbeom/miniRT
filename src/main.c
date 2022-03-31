/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyu <jaeyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:25:12 by jaeyu             #+#    #+#             */
/*   Updated: 2022/03/31 15:18:24 by jaeyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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