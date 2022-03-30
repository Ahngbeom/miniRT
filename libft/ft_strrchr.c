/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseol <jseol@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 15:28:15 by jseol             #+#    #+#             */
/*   Updated: 2021/07/11 16:37:08 by jseol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp_s;
	char	tmp_c;
	size_t	i;

	tmp_s = (char *)s;
	tmp_c = (char)c;
	i = ft_strlen(s);
	while (i > 0)
	{
		if (tmp_s[i] == tmp_c)
			return (tmp_s + i);
		i--;
	}
	if (tmp_s[i] == tmp_c)
		return (tmp_s);
	return (0);
}
