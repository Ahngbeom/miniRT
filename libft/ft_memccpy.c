/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseol <jseol@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 08:04:01 by jseol             #+#    #+#             */
/*   Updated: 2021/07/11 16:30:12 by jseol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*tmp;
	unsigned char	*s;
	unsigned char	tmp_c;
	size_t			i;

	tmp = (unsigned char *)dst;
	s = (unsigned char *)src;
	tmp_c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (s[i] == tmp_c)
		{
			tmp[i] = s[i];
			break ;
		}
		tmp[i] = s[i];
		i++;
	}
	if (i == n)
		return (0);
	return ((unsigned char *)dst + i + 1);
}
