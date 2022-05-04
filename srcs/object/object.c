/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseol <jseol@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 21:08:08 by bahn              #+#    #+#             */
/*   Updated: 2022/05/04 18:37:09 by jseol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	*object_init(t_object_type type, void *element, t_color3 color)
{
	t_object	*new;

	new = ft_calloc(sizeof(t_object), 1);
	if (new == NULL)
		return (NULL);
	new->type = type;
	new->element = element;
	new->color = color;
	new->next = NULL;
	return (new);
}

void	object_add(t_object **list, t_object *new)
{
	t_object	*ptr;

	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	ptr = *list;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new;
}

t_object	*object_last(t_object *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

void	object_clear(t_object **list)
{
	t_object	*next;

	while (*list != NULL)
	{
		next = (*list)->next;
		free((*list)->element);
		free(*list);
		*list = next;
	}
}
