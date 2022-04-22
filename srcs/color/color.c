/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 02:51:10 by bahn              #+#    #+#             */
/*   Updated: 2022/04/06 19:32:22 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	minirt_pixel_put_vector(t_img_data *data, int x, int y, t_color3 color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = (int)(color.x) << 16 | (int)(color.y) << 8 | (int)(color.z);
}

t_color3	write_color(int fd, t_color3 color)
{
	(void)fd;
	// if (fd >= 0)
	// {
	// 	ft_putnbr_fd((int)(255.999 * color.x), fd);
	// 	ft_putchar_fd(' ', fd);
	// 	ft_putnbr_fd((int)(255.999 * color.y), fd);
	// 	ft_putchar_fd(' ', fd);
	// 	ft_putnbr_fd((int)(255.999 * color.z), fd);
	// 	ft_putchar_fd('\n', fd);
	// }
	// return (vector_init(255.999 * color.x, 255.999 * color.y, 255.999 * color.z));
	return (vector_init(255.999 * color.x, 255.999 * color.y, 255.999 * color.z));
}
