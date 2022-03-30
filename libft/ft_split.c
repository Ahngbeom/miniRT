/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseol <jseol@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 12:13:23 by jseol             #+#    #+#             */
/*   Updated: 2021/07/11 16:35:59 by jseol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char set)
{
	if (c == set)
		return (1);
	else
		return (0);
}

static int	get_size(char const *s, char set)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (s[i])
	{
		if (is_set(s[i], set))
		{
			i++;
			continue ;
		}
		size++;
		while (!is_set(s[i], set) && s[i])
			i++;
	}
	return (size);
}

static char	**putret(char **ret, char const *s, char c)
{
	int		i;
	int		cnt;
	int		pivot;

	i = 0;
	cnt = 0;
	while (s[i] != '\0')
	{
		if (is_set(s[i], c))
		{
			i++;
			continue ;
		}
		pivot = i;
		while (!is_set(s[i], c) && s[i] != '\0')
			i++;
		ret[cnt] = (char *)malloc(sizeof(char) * (i - pivot + 1));
		if (ret[cnt] == NULL)
			return (NULL);
		ft_memcpy(ret[cnt], s + pivot, i - pivot);
		ret[cnt][i - pivot] = '\0';
		cnt++;
	}
	ret[cnt] = NULL;
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	int		ret_size;

	if (s == 0)
		return (0);
	ret_size = get_size(s, c);
	ret = (char **)malloc(sizeof(char *) * (ret_size + 1));
	if (ret == NULL)
		return (NULL);
	return (putret(ret, s, c));
}
