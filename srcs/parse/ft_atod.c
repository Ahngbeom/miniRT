/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseol <jseol@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:23:50 by jaeyu             #+#    #+#             */
/*   Updated: 2022/05/04 16:49:39 by jseol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	ten_to(int pow)
{
	int		i;
	double	result;

	result = 1;
	i = 0;
	while (i < pow)
	{
		result /= 10;
		i++;
	}
	return (result);
}

static double	dot_part(char *str, int *len)
{
	int		i;
	double	ret;

	i = 0;
	ret = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret *= 10;
		ret += str[i] - '0';
		i++;
	}
	ret *= ten_to(i);
	*len += i;
	return (ret);
}

double	ft_atod(char *str)
{
	int		i;
	double	sign;
	double	ret;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	ret = 0;
	while (('0' <= str[i]) && (str[i] <= '9'))
	{
		ret *= 10;
		ret += (str[i++] - '0');
	}
	if (str[i] == '.')
	{
		i++;
		ret += dot_part(&str[i], &i);
	}
	return (ret * sign);
}
