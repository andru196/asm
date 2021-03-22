/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_carry.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 18:53:09 by ycorrupt          #+#    #+#             */
/*   Updated: 2021/03/22 23:14:12 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

// sega probably here ./corewar -g corFiles/Car.cor corFiles/ex.cor corFiles/Car.cor
// sega probably here ./corewar -g 42-Corewar-Checker/champions/helltrain.cor 42-Corewar-Checker/champions/Car.cor

void	update_one_carry(intptr_t pos, t_world *nexus)
{
	if (!(nexus->flags & 2))
		return ;
	nexus->visual->a_arena[pos].value = \
		(nexus->visual->a_arena[pos].value >> (sizeof(short) * 8)) \
		<< (sizeof(short) * 8) | \
		ft_swap_colors((short int)nexus->visual->a_arena[pos].value);
}

void	update_visual_carry(t_carry *carry, intptr_t length, t_world *nexus)
{
	if (!(nexus->flags & 2))
		return ;
	update_one_carry(carry->pos, nexus);
	update_one_carry(carry->pos - length, nexus);
	/*
	nexus->visual->a_arena[carry->pos] =
		((short int)ft_swap_colors(nexus->visual->a_arena[carry->pos]));
	nexus->visual->a_arena[carry->pos - length] =
		ft_swap_colors((short int)(nexus->visual->a_arena[carry->pos - length]));
	*/
}

// TODO: тут сломан цикл снова, сегу не выдает, просто затирает соседнюю память. как.
// ./corewar -g corFiles/Car.cor corFiles/ex.cor corFiles/Car.cor
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
	mvwprintw(nexus->visual->info_window, 1, 1, "!!magic:%d!!, !!offset:%d!!, !!RTP:%d!!", (int)magic, (int)offset, (int)(sizeof(RTP)));
	wrefresh(nexus->visual->info_window);
	while(tmp <= (intptr_t)(offset + sizeof(RTP) - magic))
	{
		nexus->visual->a_arena[tmp].value = \
		nexus->visual->colors[(carry->parent->id % COLOR_PAIR_NUM)] | A_BOLD;
		nexus->visual->a_arena[tmp].bold_cycle = BOLD_CYCLE;
		++tmp;
	}
	tmp = magic;
	if (magic)
		while (tmp >= 0)
			nexus->visual->a_arena[tmp--].value = \
		nexus->visual->colors[(carry->parent->id % COLOR_PAIR_NUM)] | A_BOLD;
}
