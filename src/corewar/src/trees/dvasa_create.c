/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dvasa_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <mschimme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 16:44:05 by mschimme          #+#    #+#             */
/*   Updated: 2021/04/10 21:19:44 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>
/*
*	ПРОВЕРИЛ.
*/
t_dvasa	*ft_create_leafnode_r(void const *content, size_t content_size)
{
	t_dvasa	*new;

	new = (t_dvasa *)ft_memalloc(sizeof(t_dvasa));
	if (!new)
		return ((void *)(size_t)ft_err_malloc("new", __func__) - 1);
	new->gen.content = (void *)content;
	if (content)
		new->content_size = content_size;
	return (new);
}

/*
**	TD:	Удалить / Оставить. Нигде не используется.
*/
t_dvasa	*ft_create_leafnode(void const *content, size_t content_size)
{
	t_dvasa	*new;

	new = (t_dvasa *)ft_memalloc(sizeof(t_dvasa));
	if (!new)
		return ((void *)(size_t)ft_err_malloc("new", __func__) - 1);
	if (content)
	{
		new->gen.content = (void *)ft_memalloc(content_size);
		if (!new->gen.content)
		{
			free(new);
			return ((void *)(size_t)ft_err_malloc("content", __func__) - 1);
		}
		new->gen.content = ft_memcpy(new->gen.content, content, content_size);
		new->content_size = content_size;
	}
	return (new);
}
