/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visual.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 23:10:36 by ycorrupt          #+#    #+#             */
/*   Updated: 2021/03/30 23:50:20 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

static void		ft_init_zero_arena(t_world *nexus)
{
	t_attribute		*a_arena;
	RTP				i;

	i = -1;
	a_arena = nexus->visual->a_arena;
	while (++i < MEM_SIZE)
	{
		a_arena[i].value = nexus->visual->colors[DEFAULT_COLOR];
		a_arena[i].bold_cycle = 0;
	}
}

void			ft_init_a_arena(t_world *nexus)
{
	RTP				i;
	RTP				offset;
	t_champ			**tmp;
	t_attribute		*a_arena;

	tmp = nexus->champ_ord;
	offset = MEM_SIZE / nexus->champs;
	a_arena = nexus->visual->a_arena;
	ft_init_zero_arena(nexus);
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
				COLOR_PAIR(nexus->visual->colors[(*tmp)->id % COLOR_PAIR_NUM]);
			++i;
		}
		tmp++;
	}
}

t_visual		*ft_init_visual(void)
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
	result->info_window = \
			newwin(FIELD_HEIGTH, INFO_WIDTH, INDENT, ARENA_WIDTH + INDENT);
	result->active = 0;
	result->cycle_speed = 50;
	box(result->arena_window, 0, 0);
	refresh();
	wrefresh(result->arena_window);
	return (result);
}
