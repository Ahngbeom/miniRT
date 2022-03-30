/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseol <jseol@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 14:35:12 by jseol             #+#    #+#             */
/*   Updated: 2021/07/11 16:28:51 by jseol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*tmp_s;
	char	tmp_c;

	tmp_s = (char *)s;
	tmp_c = c;
	i = 0;
	while (tmp_s[i] != tmp_c)
	{
		if (tmp_s[i] == '\0')
			return (NULL);
		i++;
	}
	return (&tmp_s[i]);
}
