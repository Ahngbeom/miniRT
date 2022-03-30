/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 15:47:03 by bahn              #+#    #+#             */
/*   Updated: 2021/08/22 16:24:59 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	int		i;
	int		src_len;
	char	*cpy;

	i = 0;
	src_len = ft_strlen(src);
	cpy = malloc(sizeof(char) * src_len + 1);
	if (!cpy)
		return (NULL);
	while (i < src_len)
	{
		cpy[i] = src[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
