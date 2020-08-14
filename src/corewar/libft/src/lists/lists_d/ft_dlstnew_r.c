/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew_r.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 21:05:13 by mschimme          #+#    #+#             */
/*   Updated: 2020/07/01 16:12:46 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	This function creates new list and _links_ given content with it. It does
**	not dupes content data as it is done my standard ft_lstnew.
*/

t_dlist		*ft_dlstnew_r(void const *content, size_t content_size)
{
	t_dlist	*result;

	if (!(result = (t_dlist *)ft_memalloc(sizeof(t_dlist))))
		return ((void *)(size_t)ft_err_varoverflow(__ERR(total), __func__) - 1);
	result->content = (void *)content;
	if (content)
		result->content_size = content_size;
	result->next = NULL;
	result->prev = NULL;
	return (result);
}
