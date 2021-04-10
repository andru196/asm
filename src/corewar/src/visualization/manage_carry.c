/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_carry.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 18:53:09 by ycorrupt          #+#    #+#             */
/*   Updated: 2021/04/10 16:59:32 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

static void	change_attribute(t_world *nexus, intptr_t tmp, t_carry *carry)
{
	nexus->visual->a_arena[tmp].value = \
			COLOR_PAIR(nexus->visual->colors[(carry->parent->id % \
											COLOR_PAIR_NUM)]) | A_BOLD;
	nexus->visual->a_arena[tmp].bold_cycle = BOLD_CYCLE;
}

void	update_one_carry(intptr_t pos, t_world *nexus, t_bool del_carry)
{
	short	oft;
	short	current_color;
	short	new_color;

	oft = sizeof(short) * 8;
	if (!(nexus->flags & 2))
		return ;
	pos = ft_calc_addr(pos);
	current_color = (short)nexus->visual->a_arena[pos].value;
	new_color = \
		ft_swap_colors(PAIR_NUMBER((short)nexus->visual->a_arena[pos].value));
	if (del_carry == 1 && PAIR_NUMBER(current_color) > PAIR_NUMBER(new_color))
		return ;
	if (del_carry == 0 && PAIR_NUMBER(current_color) < PAIR_NUMBER(new_color))
		return ;
	nexus->visual->a_arena[pos].value = \
	(nexus->visual->a_arena[pos].value >> oft) << oft | new_color;
}

void	update_visual_carry(t_carry *carry, intptr_t length, t_world *nexus)
{
	if (!(nexus->flags & 2))
		return ;
	update_one_carry(carry->pos, nexus, 0);
	update_one_carry(carry->pos - length, nexus, 1);
}

void	color_bytecode(t_carry *carry, t_world *nexus, intptr_t offset)
{
	intptr_t	tmp;
	intptr_t	magic;

	if (!(nexus->flags & 2))
		return ;
	offset = ft_calc_addr(offset);
	magic = ((offset + sizeof(RTP)) % MEM_SIZE) * \
										((offset + sizeof(RTP)) / MEM_SIZE);
	tmp = offset;
	while (tmp < (intptr_t)(offset + sizeof(RTP) - magic))
	{
		change_attribute(nexus, tmp, carry);
		++tmp;
	}
	tmp = magic;
	if (magic)
	{
		while (tmp >= 0)
		{
			change_attribute(nexus, tmp, carry);
			tmp--;
		}
	}
}
