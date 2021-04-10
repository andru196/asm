/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dvasa_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <mschimme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 19:06:25 by mschimme          #+#    #+#             */
/*   Updated: 2021/04/10 14:45:35 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

/*
*	ПРОВЕРИЛ.
**	In order this shit working correctcly you ought to provide ->RIGHT of the
**	aleaf.
*/
void	ft_add_leafnode(t_dvasa **aleaf, t_dvasa *new)
{
	if (!new || !aleaf)
		return ;
	if (*aleaf)
	{
		new->right.du_vasa = (*aleaf)->right.du_vasa;
		(*aleaf)->right.du_vasa = new;
		*aleaf = new;
	}
}