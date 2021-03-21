/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_field.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 23:10:36 by ycorrupt          #+#    #+#             */
/*   Updated: 2021/03/21 23:25:17 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>


void		ft_print_info_playes(t_world *nexus, int *cursor)
{
	t_champ **tmp = nexus->champ_ord;
	int i;

	i = 0;
	while (*tmp)
	{
		wattron(nexus->visual->info_window, nexus->visual->colors[((*tmp)->id % COLOR_PAIR_NUM)]);
		mvwprintw(nexus->visual->info_window, *cursor += 2, INDENT, "Player %d: %s", (*tmp)->id, (*tmp)->name);
		wattroff(nexus->visual->info_window, nexus->visual->colors[((*tmp)->id % COLOR_PAIR_NUM)]);
		tmp++;
	}
	wrefresh(nexus->visual->info_window);
}

void		ft_print_info(t_world *nexus)
{
	int i;
	char *hello_string;
	WINDOW *iw = nexus->visual->info_window;

	i = INDENT;
	hello_string = "Hello to our cool (maybe) COREWAR!!!";
	werase(iw);
	box(iw, 0, 0); 
	wattron(iw, A_BOLD);
	mvwprintw(iw, 2, INDENT, "%s", nexus->visual->active ? "** RUNNING **" : "** PAUSED **");
	mvwprintw(iw, i += 2, INFO_WIDTH / 2 - ft_strlen(hello_string) / 2, "%s", hello_string);
	mvwprintw(iw, i += 2, INDENT, "%s %d", "Cycle/second limit: ", nexus->visual->cycle_speed);
	mvwprintw(iw, i += 2, INDENT, "%s %d", "Cycle: ", nexus->cyc.cycle);
	mvwprintw(iw, i += 2, INDENT, "%s %d", "Processes: ", nexus->champs);
	ft_print_info_playes(nexus, &i);
	mvwprintw(iw, i += 2, INDENT, "%s %d", "CYCLE_TO_DIE: ", nexus->cyc.cyc_to_die);
	mvwprintw(iw, i += 2, INDENT, "%s %d", "CYCLE_DELTA: ", nexus->cyc.cycle_delta);
	mvwprintw(iw, i += 2, INDENT, "%s %d", "NBR_LIVE: ", nexus->cyc.cyc_to_die);
	mvwprintw(iw, i += 2, INDENT, "%s %d", "MAX_CHECKS: ", MAX_CHECKS);
	wrefresh(iw);
	wattroff(iw, A_BOLD);
}

void			ft_init_a_arena(t_world *nexus)
{
	RTP		i;
	RTP		offset;
	t_champ	**tmp;

	tmp = nexus->champ_ord;
	offset = MEM_SIZE / nexus->champs;
	i = -1;
	while (++i < MEM_SIZE)
		nexus->visual->a_arena[i].value = nexus->visual->colors[DEFAULT_COLOR];
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
