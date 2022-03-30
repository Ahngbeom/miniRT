/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseol <jseol@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 18:04:09 by jseol             #+#    #+#             */
/*   Updated: 2021/07/11 16:31:25 by jseol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *),
void (*del)(void *))
{
	t_list	*new_head;
	t_list	*new_lst;
	t_list	*cur;

	if (lst == NULL || f == NULL)
		return (NULL);
	new_head = ft_lstnew(f(lst->content));
	if (new_head == NULL)
		return (NULL);
	cur = new_head;
	lst = lst->next;
	while (lst != NULL)
	{
		new_lst = ft_lstnew(f(lst->content));
		if (new_lst == NULL)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		cur->next = new_lst;
		cur = new_lst;
		lst = lst->next;
	}
	return (new_head);
}
