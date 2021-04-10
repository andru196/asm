/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 23:40:13 by mschimme          #+#    #+#             */
/*   Updated: 2019/03/06 20:07:45 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*start;
	t_list	*previous;

	start = NULL;
	if (!lst || !f)
		return (NULL);
	start = f(lst);
	previous = start;
	lst = lst->next;
	while (lst)
	{
		if (!as((void **)&new, f(lst)))
			return (NULL);
		previous->next = new;
		previous = previous->next;
		lst = lst->next;
	}
	return (start);
}
