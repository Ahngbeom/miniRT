/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:19:28 by bahn              #+#    #+#             */
/*   Updated: 2022/04/20 13:11:48 by bahn             ###   ########.fr       */
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

# include <math.h> // sqrt
# define __USE_XOPEN // M_PI

# define MINIRT_PI 3.14159265358979323846

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

# define CAMERA		0
# define SPHERE		1
# define PLANE		2
# define CYLINDER	3
# define SQUARE		4

# define EPSILON	1e-6

# define LUMEN		3

# include "minirt_structure.h"
# include "minirt_function.h"

#endif