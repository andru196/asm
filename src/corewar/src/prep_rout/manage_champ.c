/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_champ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <mschimme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 14:04:13 by mschimme          #+#    #+#             */
/*   Updated: 2021/04/10 20:55:07 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

/*
* Проверил.
*/

void	ft_clear_champ(t_champ *this)
{
	if (this->name)
		free(this->name);
	if (this->desc)
		free(this->desc);
	if (this->body)
		free(this->body);
	this->name = NULL;
	this->desc = NULL;
	this->body = NULL;
	this->id = 0;
	this->size = 0;
}

/*
**	This function is required to surpass CHAMP_MAX_SIZE limitations.
**	Thus we could read body exceeding CHAMP_MAX_SIZE without fucking
**	malloc integrity.
*/
uint8_t	*ft_champ_body_alloc(size_t ch_size, t_vasa **champ_err)
{
	void	*body;

	body = ft_memalloc(ch_size);
	if (!body)
	{
		ft_err_malloc("Cmampion's body", __func__);
		ft_lstdel((t_list **)champ_err, &ft_del);
		ft_manage_world(NULL);
	}
	return (body);
}

/*
**	void	ft_init_champ(t_champ *this, int id, t_vasa **champ_error)
**	{
**		*champ_error = NULL;
**		this->name = (char *)ft_memalloc((PROG_NAME_LENGTH + 1 + REG_SIZE) * \
**																sizeof(char));
**		this->desc = (char *)ft_memalloc((COMMENT_LENGTH + 1 + REG_SIZE) * \
**																sizeof(char));
**		if (!this->name || !this->desc)
**		{
**			if (this->name)
**				free(this->name);
**			if (this->desc)
**				free(this->desc);
**			ft_err_malloc("Element of champion", __func__);
**			ft_manage_world(NULL);
**		}
**		this->id = id;
**	}
*/
