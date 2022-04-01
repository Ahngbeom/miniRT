/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 21:22:04 by bahn              #+#    #+#             */
/*   Updated: 2021/08/22 16:06:24 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_countstrs(char *s, char c)
{
	size_t	cnt;

	cnt = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			cnt++;
			while (*(++s) != c)
			{
				if (*s == '\0')
					break ;
			}
		}
		else
			s++;
	}
	return (cnt);
}

static	char	*ft_findstr(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
			s++;
		else
			return (s);
	}
	return (0);
}

static	size_t	ft_strclen(char *s, char c)
{
	size_t	length;
	char	*ptr;

	length = 0;
	ptr = s;
	while (*ptr != '\0' && *ptr != c)
	{
		length++;
		ptr++;
	}
	return (length);
}

static	char	**ft_splitter(char **pptr, char *str_ptr, char c, \
		size_t str_cnt)
{
	size_t	i;

	i = 0;
	while (i < str_cnt)
	{
		pptr[i] = (char *)malloc(ft_strclen(ft_findstr(str_ptr, c), c) + 1);
		if (pptr[i] == NULL)
		{
			while (pptr[i] != NULL)
				free(pptr[i++]);
			free(pptr);
			return (pptr);
		}
		ft_strlcpy(pptr[i], ft_findstr(str_ptr, c), \
				ft_strclen(ft_findstr(str_ptr, c), c) + 1);
		str_ptr = ft_findstr(ft_findstr(str_ptr, c) + \
				ft_strclen(ft_findstr(str_ptr, c), c), c);
		i++;
	}
	pptr[i] = NULL;
	return (pptr);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	char	*sptr;
	size_t	cnt_strs;

	if (!s)
		return (NULL);
	sptr = (char *)s;
	cnt_strs = ft_countstrs(sptr, c);
	result = (char **)malloc(sizeof(char *) * (cnt_strs + 1));
	if (result == NULL)
		return (NULL);
	return (ft_splitter(result, sptr, c, cnt_strs));
}
