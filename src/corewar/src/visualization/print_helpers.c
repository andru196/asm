/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 21:36:10 by ycorrupt          #+#    #+#             */
/*   Updated: 2021/03/27 22:04:20 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

static void		ft_print_info_playes(t_world *nexus, int *cursor)
{
	t_champ **tmp = nexus->champ_ord;
	int i;
	WINDOW *iw;

	iw = nexus->visual->info_window;
	i = 0;
	while (*tmp)
	{
		wattron(iw, COLOR_PAIR(nexus->visual->colors[((*tmp)->id % COLOR_PAIR_NUM)]));
		mvwprintw(iw, *cursor += 2, INDENT, "Player %d: %s", \
												(*tmp)->id, (*tmp)->name);
		mvwprintw(iw, *cursor += 2, INDENT, "Last live: %d", \
												(*tmp)->last_live_op);
		wattroff(iw, COLOR_PAIR(nexus->visual->colors[((*tmp)->id % COLOR_PAIR_NUM)]));
		wrefresh(iw);
		tmp++;
	}
}

void		    ft_print_info(t_world *nexus)
{
	int i;
	char *hello_string;
	WINDOW *iw;

	iw = nexus->visual->info_window;
	i = INDENT;
	hello_string = "Hello to our cool (maybe) COREWAR!!!";
	//werase(iw);
	box(iw, 0, 0);
	wattron(iw, A_BOLD);
	mvwprintw(iw, 2, INDENT, "%s", nexus->visual->active ? "** RUNNING **" : "** PAUSED **");
	mvwprintw(iw, i += 2, INFO_WIDTH / 2 - ft_strlen(hello_string) / 2, "%s", hello_string);
	mvwprintw(iw, i += 2, INDENT, "%s %d", "Cycle/second limit: ", nexus->visual->cycle_speed);
	mvwprintw(iw, i += 2, INDENT, "%s %d", "Cycle: ", nexus->cyc.cycle);
	mvwprintw(iw, i += 2, INDENT, "%s %d", "Champs: ", nexus->champs);
	ft_print_info_playes(nexus, &i);
	mvwprintw(iw, i += 2, INDENT, "%s %d", "CYCLE_TO_DIE: ", nexus->cyc.cyc_to_die);
	mvwprintw(iw, i += 2, INDENT, "%s %d", "CYCLE_DELTA: ", nexus->cyc.cycle_delta);
	mvwprintw(iw, i += 2, INDENT, "%s %d", "NBR_LIVE: ", nexus->cyc.cyc_to_die);
	mvwprintw(iw, i += 2, INDENT, "%s %d", "MAX_CHECKS: ", MAX_CHECKS);
	wrefresh(iw);
	wattroff(iw, A_BOLD);
}

void			ft_print_ncursus_arena(t_world *nexus)
{
	size_t			i;
	size_t			j;
	size_t			x;
	char			temp[2];
	uint8_t			*arena;

	i = 0;
	arena = nexus->arena + sizeof(RTP);
	while (i < 64)
	{
		j = 0;
		x = 2;
		while (j < 64)
		{
			wattron(nexus->visual->arena_window, nexus->visual->a_arena[i * 64 + j].value);
			temp[0] = arena[i * 64 + j] / 16;
			temp[0] = temp[0] + (temp[0] > 9 ? 'a' - 10 : '0');
			temp[1] = arena[i * 64 + j] % 16;
			temp[1] = temp[1] + (temp[1] > 9 ? 'a' - 10 : '0');
			mvwprintw(nexus->visual->arena_window, i + 1, x, "%c%c", temp[0], temp[1]);
			wattroff(nexus->visual->arena_window, nexus->visual->a_arena[i * 64 + j].value);
			mvwprintw(nexus->visual->arena_window, i + 3, x + 2, " ");
			j++;
			x +=3;
		}
		wrefresh(nexus->visual->arena_window);
		i++;
	}
}

void			update_attribute_arena(t_world *nexus)
{
	int i;
	t_attribute *a_arena;

	a_arena = nexus->visual->a_arena;
	i = MEM_SIZE;
	while (--i >= 0)
	{
		if (a_arena[i].bold_cycle != 0)
		{
			--a_arena[i].bold_cycle;
			if (a_arena[i].bold_cycle == 0)
				a_arena[i].value = a_arena[i].value ^ A_BOLD;
		}
	}
}
