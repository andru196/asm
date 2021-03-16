/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 18:53:09 by ycorrupt          #+#    #+#             */
/*   Updated: 2021/03/17 00:29:22 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

void	update_visual_carry(t_carry *carry, intptr_t length, t_world *nexus)
{
	nexus->visual->attribute_arena[carry->pos] =
		((short int)ft_swap_colors(nexus->visual->attribute_arena[carry->pos]));
	nexus->visual->attribute_arena[carry->pos - length] =
		ft_swap_colors((short int)(nexus->visual->attribute_arena[carry->pos - length]));
}

/////////////////// TODO: magic stuff(((((((((
void	color_bytecode(t_carry *carry, t_world *nexus, intptr_t offset)
{
	intptr_t	tmp;
	intptr_t	magic;

	offset = ft_calc_addr(offset);
	tmp = offset;
	while(tmp != offset + 4)
	{
		nexus->visual->attribute_arena[tmp] = \
							nexus->visual->colors[(carry->parent->id % COLOR_PAIR_NUM)];
		tmp++;
	}
}