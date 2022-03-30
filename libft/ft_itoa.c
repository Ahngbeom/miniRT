/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseol <jseol@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 12:54:06 by jseol             #+#    #+#             */
/*   Updated: 2021/07/11 16:41:42 by jseol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*putret(char *buf)
{
	char	*ret;
	int		i;

	ret = (char *)malloc(sizeof(char) * (ft_strlen(buf) + 1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (buf[i] != '\0')
	{
		ret[i] = buf[ft_strlen(buf) - i - 1];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*ft_itoa(int n)
{
	char	buf[42];
	int		i;
	int		sign;

	sign = 1;
	if (n < 0)
		sign *= -1;
	i = 0;
	while (1)
	{
		buf[i] = sign * ((n % 10)) + '0';
		n /= 10;
		i++;
		if (n == 0)
			break ;
	}
	if (sign == -1)
	{
		buf[i] = '-';
		i++;
	}
	buf[i] = '\0';
	return (putret(buf));
}
