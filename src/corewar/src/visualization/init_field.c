/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_field.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 23:10:36 by ycorrupt          #+#    #+#             */
/*   Updated: 2021/03/03 00:12:30 by ycorrupt         ###   ########.fr       */
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
		mvwprintw(nexus->visual->info_window, *cursor += 2, INDENT, "Player %d: %s", (*tmp)->id, (*tmp)->name);
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
	wattron(nexus->visual->info_window, A_BOLD);
	mvwprintw(nexus->visual->info_window, 2, INDENT, "%s", nexus->visual->active ? "** RUNNING **" : "** PAUSED **");
	mvwprintw(nexus->visual->info_window, i += 2, INFO_WIDTH / 2 - ft_strlen(hello_string) / 2, "%s", hello_string);
	mvwprintw(nexus->visual->info_window, i += 2, INDENT, "%s %d", "Cycle/second limit: ", 555555);
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

t_visual		*ft_init_field(t_world *nexus)
{
	t_visual *result;

    initscr();
	noecho();
	timeout(1);
	//start_color();
	result = (t_visual *)ft_memalloc(sizeof(t_visual));
	result->arena_window = newwin(FIELD_HEIGTH, ARENA_WIDTH, INDENT, INDENT);
	result->info_window = newwin(FIELD_HEIGTH, INFO_WIDTH, INDENT, ARENA_WIDTH + INDENT);
	result->active = 0;
    refresh();
	box(result->arena_window, 0, 0);
	box(result->info_window, 0, 0); 
	wrefresh(result->arena_window);
	wrefresh(result->info_window);
	return (result);
}
