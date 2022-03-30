/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseol <jseol@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 15:51:21 by jseol             #+#    #+#             */
/*   Updated: 2021/11/07 14:02:41 by jseol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_char_check(char str)
{
	if (str == ' ' || str == '\f' || str == '\n' || str == '\r'
		|| str == '\t' || str == '\v' || str == '+')
		return (1);
	else if (str == '-')
		return (-1);
	else
		return (0);
}

int	ft_base_check(char *base, int base_size)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	tmp = base;
	while (tmp[i] != '\0')
	{
		if (tmp[0] == '\0' || base_size == 1)
			return (0);
		if (tmp[i] == '+' || tmp[i] == '-' || tmp[i] == ' ' || tmp[i] == '\f'
			|| tmp[i] == '\n' || tmp[i] == '\r'
			|| tmp[i] == '\t' || tmp[i] == '\v')
			return (0);
		j = i + 1;
		while (tmp[j] != '\0')
		{
			if (tmp[i] == tmp[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	find_index(char c, char *base, int base_size)
{
	int	i;

	i = 0;
	while (i < base_size)
	{
		if (c == base[i])
			return (i);
		i++;
	}
	return (-1);
}

int	ft_putnbr_base(char *str, char *base, int base_size)
{
	int	i;
	int	sign;
	int	ret;

	i = 0;
	sign = 1;
	ret = 0;
	while (ft_char_check(str[i]))
	{
		sign *= ft_char_check(str[i]);
		i++;
	}
	while (str[i] != '\0')
	{
		if (!(find_index(str[i], base, base_size) == -1))
		{
			ret *= base_size;
			ret += find_index(str[i], base, base_size) * sign;
			i++;
		}
		else
			break ;
	}
	return (ret);
}

int	ft_atoi_base(char *str, char *base)
{
	int	i;
	int	nbr;
	int	base_size;

	i = 0;
	nbr = 0;
	base_size = 0;
	while (base[base_size] != '\0')
		base_size++;
	if (ft_base_check(base, base_size))
		nbr = ft_putnbr_base(str, base, base_size);
	return (nbr);
}
