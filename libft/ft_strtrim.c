/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseol <jseol@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 11:21:59 by jseol             #+#    #+#             */
/*   Updated: 2021/07/11 16:39:41 by jseol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	size_t	start;
	size_t	end;
	size_t	i;
	size_t	s_len;

	if (s1 == 0 || set == 0)
		return (0);
	i = 0;
	while (is_set(s1[i], set))
		i++;
	start = i;
	s_len = ft_strlen(s1);
	if (s1[i] == '\0')
		return (ft_strdup(""));
	i = 0;
	while (is_set(s1[s_len - i - 1], set))
		i++;
	end = i;
	ret = (char *)malloc(sizeof(char) * (s_len - start - end + 1));
	if (ret == NULL)
		return (NULL);
	ft_memcpy(ret, s1 + start, s_len - start - end);
	ret[s_len - start - end] = 0;
	return (ret);
}
