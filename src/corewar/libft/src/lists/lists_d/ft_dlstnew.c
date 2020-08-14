/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 21:05:13 by mschimme          #+#    #+#             */
/*   Updated: 2020/07/01 16:13:11 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist		*ft_dlstnew(void const *content, size_t content_size)
{
	t_dlist	*res;

	if (!(res = (t_dlist *)ft_memalloc(sizeof(t_dlist))))
		return ((void *)(size_t)ft_err_varoverflow(__ERR(res), __func__) - 1);
	if (!content)
	{
		res->content = NULL;
		res->content_size = 0;
	}
	else
	{
		if (!(res->CNT = (void *)ft_memalloc(content_size)))
		{
			free(res);
			return ((void *)(size_t)ft_err_varoverflow(__ERR(res->CNT), \
						__func__) - 1);
		}
		res->content = ft_memcpy(res->content, content, content_size);
		res->content_size = content_size;
	}
	res->next = NULL;
	res->prev = NULL;
	return (res);
}
