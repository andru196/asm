/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visual.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 23:10:36 by ycorrupt          #+#    #+#             */
/*   Updated: 2021/03/22 22:51:17 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

void			ft_init_a_arena(t_world *nexus)
{
	RTP				i;
	RTP				offset;
	t_champ			**tmp;
	t_attribute		*a_arena;

	tmp = nexus->champ_ord;
	offset = MEM_SIZE / nexus->champs;
	a_arena = nexus->visual->a_arena;
	i = -1;
	while (++i < MEM_SIZE)
	{
		a_arena[i].value = nexus->visual->colors[DEFAULT_COLOR];
		a_arena[i].bold_cycle = 0;
	}
	while (*tmp)
	{
		i = ((*tmp)->id - 1) * offset;
		while (i < (RTP)(((*tmp)->id - 1) * offset + (*tmp)->size))
		{
			if (i == ((*tmp)->id - 1) * offset)
				nexus->visual->a_arena[i].value = \
				ft_swap_colors(nexus->visual->colors[(*tmp)->id % COLOR_PAIR_NUM]);
			else
				nexus->visual->a_arena[i].value = \
				nexus->visual->colors[(*tmp)->id % COLOR_PAIR_NUM];
			++i;
		}
		tmp++;
	}
}

t_visual		*ft_init_visual()
{
	t_visual *result;

    initscr();
	noecho();
	curs_set(0); // hide cursor
	timeout(1); // timeout for input (getch)
	start_color();
	result = (t_visual *)ft_memalloc(sizeof(t_visual));
	ft_init_colors(result->colors);
	result->arena_window = newwin(FIELD_HEIGTH, ARENA_WIDTH, INDENT, INDENT);
	result->info_window = newwin(FIELD_HEIGTH, INFO_WIDTH, INDENT, ARENA_WIDTH + INDENT);
	result->active = 0;
	result->cycle_speed = 50;
    refresh();
	box(result->arena_window, 0, 0);
	wrefresh(result->arena_window);
	wrefresh(result->info_window);
	return (result);
}
