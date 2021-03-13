/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_field.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 23:10:36 by ycorrupt          #+#    #+#             */
/*   Updated: 2021/03/13 23:15:57 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

void		ft_init_colors()
{
	init_pair(DEFAULT_COLOR, COLOR_WHITE, COLOR_BLACK);
	init_pair(MAGENTA_PAIR, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(BLUE_PAIR, COLOR_BLUE, COLOR_BLACK);
	init_pair(YELLOW_PAIR, COLOR_YELLOW, COLOR_BLACK);
	init_pair(GREEN_PAIR, COLOR_GREEN, COLOR_BLACK);
	init_pair(CARRIAGE_MAGENTA_PAIR, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(CARRIAGE_BLUE_PAIR, COLOR_BLACK, COLOR_BLUE);
	init_pair(CARRIAGE_YELLOW_PAIR, COLOR_BLACK, COLOR_YELLOW);
	init_pair(CARRIAGE_GREEN_PAIR, COLOR_BLACK, COLOR_GREEN);
}

void		ft_print_info_playes(t_world *nexus, int *cursor)
{
	t_champ **tmp = nexus->champ_ord;
	int i;

	i = 0;
	while (*tmp)
	{
		wattron(nexus->visual->info_window, COLOR_PAIR(((*tmp)->id % COLOR_PAIR_NUM) + 1));
		mvwprintw(nexus->visual->info_window, *cursor += 2, INDENT, "Player %d: %s", (*tmp)->id, (*tmp)->name);
		wattroff(nexus->visual->info_window, COLOR_PAIR(((*tmp)->id % COLOR_PAIR_NUM) + 1));
		tmp++;
	}
	wrefresh(nexus->visual->info_window);
}

void		ft_print_info(t_world *nexus)
{
	int i;
	char *hello_string;

	i = INDENT;
	hello_string = "Hello to our cool (maybe) COREWAR!!!";
	werase(nexus->visual->info_window);
	box(nexus->visual->info_window, 0, 0); 
	wattron(nexus->visual->info_window, A_BOLD);
	mvwprintw(nexus->visual->info_window, 2, INDENT, "%s", nexus->visual->active ? "** RUNNING **" : "** PAUSED **");
	mvwprintw(nexus->visual->info_window, i += 2, INFO_WIDTH / 2 - ft_strlen(hello_string) / 2, "%s", hello_string);
	mvwprintw(nexus->visual->info_window, i += 2, INDENT, "%s %d", "Cycle/second limit: ", nexus->visual->cycle_speed);
	mvwprintw(nexus->visual->info_window, i += 2, INDENT, "%s %d", "Cycle: ", nexus->cyc.cycle);
	mvwprintw(nexus->visual->info_window, i += 2, INDENT, "%s %d", "Processes: ", nexus->champs);
	ft_print_info_playes(nexus, &i);
	mvwprintw(nexus->visual->info_window, i += 2, INDENT, "%s %d", "CYCLE_TO_DIE: ", nexus->cyc.cyc_to_die);
	mvwprintw(nexus->visual->info_window, i += 2, INDENT, "%s %d", "CYCLE_DELTA: ", nexus->cyc.cycle_delta);
	mvwprintw(nexus->visual->info_window, i += 2, INDENT, "%s %d", "NBR_LIVE: ", nexus->cyc.cyc_to_die);
	mvwprintw(nexus->visual->info_window, i += 2, INDENT, "%s %d", "MAX_CHECKS: ", MAX_CHECKS);
	wrefresh(nexus->visual->info_window);
	wattroff(nexus->visual->info_window, A_BOLD);
}

void			ft_init_attribute_arena(t_world *nexus)
{
	RTP		i;
	RTP		offset;
	t_champ	**tmp;

	tmp = nexus->champ_ord;
	offset = MEM_SIZE / nexus->champs;
	i = -1;
	while (++i < MEM_SIZE)
		nexus->visual->attribute_arena[i] = COLOR_PAIR(DEFAULT_COLOR);
	while (*tmp)
	{
		i = ((*tmp)->id - 1) * offset;
		while (i < (RTP)(((*tmp)->id - 1) * offset + (*tmp)->size))
		{
			nexus->visual->attribute_arena[i] = COLOR_PAIR(((*tmp)->id % COLOR_PAIR_NUM) + 1);
			i++;
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
	ft_init_colors();
	result = (t_visual *)ft_memalloc(sizeof(t_visual));
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
