/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseol <jseol@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:36:07 by jaeyu             #+#    #+#             */
/*   Updated: 2022/05/04 18:38:36 by jseol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	split_size(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

static int	is_set(char c, char set1, char set2)
{
	if (c == set1 || c == set2)
		return (1);
	else
		return (0);
}

static int	get_size(char const *s, char set1, char set2)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (s[i])
	{
		if (is_set(s[i], set1, set2))
		{
			i++;
			continue ;
		}
		size++;
		while (!is_set(s[i], set1, set2) && s[i])
			i++;
	}
	return (size);
}

static char	**putret(char **ret, char const *s, char c1, char c2)
{
	int	i;
	int	cnt;
	int	pivot;

	i = 0;
	cnt = 0;
	while (s[i] != '\0')
	{
		if (is_set(s[i], c1, c2))
		{
			i++;
			continue ;
		}
		pivot = i;
		while (!is_set(s[i], c1, c2) && s[i] != '\0')
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

char	**ft_split2(char const *s, char c1, char c2)
{
	char	**ret;
	int		ret_size;

	if (s == 0)
		return (0);
	ret_size = get_size(s, c1, c2);
	ret = (char **)malloc(sizeof(char *) * (ret_size + 1));
	if (ret == NULL)
		return (NULL);
	return (putret(ret, s, c1, c2));
}
