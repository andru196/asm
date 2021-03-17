/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 18:53:09 by ycorrupt          #+#    #+#             */
/*   Updated: 2021/03/18 02:05:25 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

void	update_one_carry(intptr_t pos, t_world *nexus)
{
	nexus->visual->attribute_arena[pos] =
		ft_swap_colors((short int)nexus->visual->attribute_arena[pos]);
}

void	update_visual_carry(t_carry *carry, intptr_t length, t_world *nexus)
{
	update_one_carry(carry->pos, nexus);
	update_one_carry(carry->pos - length, nexus);
	/*
	nexus->visual->attribute_arena[carry->pos] =
		((short int)ft_swap_colors(nexus->visual->attribute_arena[carry->pos]));
	nexus->visual->attribute_arena[carry->pos - length] =
		ft_swap_colors((short int)(nexus->visual->attribute_arena[carry->pos - length]));
	*/
}

void	color_bytecode(t_carry *carry, t_world *nexus, intptr_t offset)
{
	intptr_t	tmp;
	intptr_t	magic;

	offset = ft_calc_addr(offset);
	magic = ((offset + sizeof(RTP)) % MEM_SIZE) * \
										((offset + sizeof(RTP)) / MEM_SIZE);
	tmp = offset;
	while(tmp != offset + 4 - magic && offset  + 4 - magic < MEM_SIZE)
	{
		nexus->visual->attribute_arena[tmp] = \
							nexus->visual->colors[(carry->parent->id % COLOR_PAIR_NUM)];
		tmp++;
	}
	tmp = magic - sizeof(RTP);
	while (tmp != magic)
	{
		if (tmp > 0)
			nexus->visual->attribute_arena[tmp] = \
							nexus->visual->colors[(carry->parent->id % COLOR_PAIR_NUM)];
		tmp++;
	}
}