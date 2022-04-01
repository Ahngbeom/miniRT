/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:19:28 by bahn              #+#    #+#             */
/*   Updated: 2022/03/30 15:40:02 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include "libft.h"

# include <fcntl.h> // open
# include <sys/stat.h> // open mode
# include <stdio.h> // printf
# define __USE_XOPEN // M_PI
# include <math.h> // sqrt

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 10240
# endif

# define WIDTH	1280
# define HEIGHT	720

# define FALSE	0
# define TRUE	1

typedef int	t_bool;
typedef	int	t_object_type;

# define SPHERE		0
# define PLANE		1
# define CYLINDER	2
# define SQUARE		3

# define EPSILON	1e-6

# include "minirt_structure.h"
# include "minirt_function.h"

#endif