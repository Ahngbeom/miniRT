/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 14:59:00 by bahn              #+#    #+#             */
/*   Updated: 2021/08/22 14:49:58 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	c = '0';
	if (fd < 0)
		return ;
	if (n >= 0)
	{
		if (n / 10 > 0)
			ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(c + (n % 10), fd);
	}
	else
	{
		ft_putchar_fd('-', fd);
		if ((n / 10) * -1 > 0)
			ft_putnbr_fd((n / 10) * -1, fd);
		ft_putchar_fd(c + ((n % 10) * -1), fd);
	}
}
