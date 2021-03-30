/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 21:36:10 by ycorrupt          #+#    #+#             */
/*   Updated: 2021/03/30 22:14:40 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

static void	ft_print_info_playes(t_world *nexus, int *cursor)
{
	t_champ		**tmp;
	t_window	*iw;
	int			i;

	tmp = nexus->champ_ord;
	iw = nexus->visual->info_window;
	i = 0;
	mvwprintw(iw, *cursor += 2, INDENT, "%s %d", "Champs: ", nexus->champs);
	while (*tmp)
	{
		wattron(iw, \
		COLOR_PAIR(nexus->visual->colors[((*tmp)->id % COLOR_PAIR_NUM)]));
		mvwprintw(iw, *cursor += 2, INDENT, "Player %d: %s", \
												(*tmp)->id, (*tmp)->name);
		mvwprintw(iw, *cursor += 2, INDENT, "Last live: %d", \
												(*tmp)->last_live_op);
		wattroff(iw, \
		COLOR_PAIR(nexus->visual->colors[((*tmp)->id % COLOR_PAIR_NUM)]));
		wrefresh(iw);
		tmp++;
	}
}

void		ft_print_winner(t_world *nexus)
{
	t_window *iw;

	iw = nexus->visual->info_window;
	wattron(iw, \
	COLOR_PAIR(nexus->visual->colors[nexus->survivor->id % COLOR_PAIR_NUM]));
	mvwprintw(iw, \
	getmaxy(iw) - INDENT, INDENT, "Winner: %s", nexus->survivor->name);
	wattroff(iw, \
	COLOR_PAIR(nexus->visual->colors[nexus->survivor->id % COLOR_PAIR_NUM]));
}

void		ft_print_info(t_world *nex)
{
	int			i;
	int			j;
	t_window	*iw;

	iw = nex->visual->info_window;
	i = INDENT;
	j = INDENT;
	werase(iw);
	box(iw, 0, 0);
	wattron(iw, A_BOLD);
	mvwprintw(iw, 2, j, "%s", \
			nex->visual->active ? "** RUNNING **" : "** PAUSED **");
	mvwprintw(iw, i += 2, \
			INFO_WIDTH / 2 - ft_strlen(HELLO_STRING) / 2, "%s", HELLO_STRING);
	mvwprintw(iw, i += 2, j, "%s %d", "Cycle/second limit: ", \
											nex->visual->cycle_speed);
	mvwprintw(iw, i += 2, j, "%s %d", "Cycle: ", nex->cyc.cycle);
	ft_print_info_playes(nex, &i);
	mvwprintw(iw, i += 2, j, "%s %d", "CYCLE_TO_DIE: ", nex->cyc.cyc_to_die);
	mvwprintw(iw, i += 2, j, "%s %d", "CYCLE_DELTA: ", nex->cyc.cycle_delta);
	mvwprintw(iw, i += 2, j, "%s %d", "NBR_LIVE: ", nex->cyc.cyc_to_die);
	mvwprintw(iw, i += 2, j, "%s %d", "MAX_CHECKS: ", MAX_CHECKS);
	wrefresh(iw);
	wattroff(iw, A_BOLD);
}

void		ft_print_bytes(t_window *aw, uint8_t p, size_t i, size_t x)
{
	char	temp[2];

	temp[0] = p / 16;
	temp[0] = temp[0] + (temp[0] > 9 ? 'a' - 10 : '0');
	temp[1] = p % 16;
	temp[1] = temp[1] + (temp[1] > 9 ? 'a' - 10 : '0');
	mvwprintw(aw, i + 1, x, "%c%c", temp[0], temp[1]);
}

void		ft_print_ncursus_arena(t_world *nexus)
{
	size_t			i;
	size_t			j;
	size_t			x;
	uint8_t			*arena;
	t_visual		*v;

	i = 0;
	arena = nexus->arena + sizeof(RTP);
	v = nexus->visual;
	while (i < 64)
	{
		j = 0;
		x = 2;
		while (j < 64)
		{
			wattron(v->arena_window, v->a_arena[i * 64 + j].value);
			ft_print_bytes(v->arena_window, arena[i * 64 + j], i, x);
			wattroff(v->arena_window, v->a_arena[i * 64 + j].value);
			j++;
			x += 3;
		}
		i++;
	}
	wrefresh(v->arena_window);
}
