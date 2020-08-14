/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <mschimme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 23:01:21 by mschimme          #+#    #+#             */
/*   Updated: 2019/12/10 20:22:42 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdelone(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*ptr;

	if (!alst || !(*alst))
		return ;
	if (del)
		del((*alst)->content, (*alst)->content_size);
	(*alst)->content = NULL;
	ptr = (*alst)->next;
	free(*alst);
	*alst = ptr;
}
