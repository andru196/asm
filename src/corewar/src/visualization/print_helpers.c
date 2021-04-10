/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 21:36:10 by ycorrupt          #+#    #+#             */
/*   Updated: 2021/04/10 02:39:37 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

static void	ft_print_info_playes(t_world *nex, int *cursor)
{
	t_champ		**tmp;
	t_window	*iw;
	int			i;

	tmp = nex->champ_ord;
	iw = nex->visual->info_window;
	i = 0;
	mvwprintw(iw, *cursor += 2, INDENT, "%s %d", "Cycle: ", nex->cyc.cycle);
	mvwprintw(iw, *cursor += 2, INDENT, "%s %d", "Champs: ", nex->champs);
	while (*tmp)
	{
		wattron(iw, \
		COLOR_PAIR(nex->visual->colors[((*tmp)->id % COLOR_PAIR_NUM)]));
		mvwprintw(iw, *cursor += 2, INDENT, "Player %d: %s", \
												(*tmp)->id, (*tmp)->name);
		mvwprintw(iw, *cursor += 2, INDENT, "Last live: %d", \
												(*tmp)->last_live_op);
		wattroff(iw, \
		COLOR_PAIR(nex->visual->colors[((*tmp)->id % COLOR_PAIR_NUM)]));
		tmp++;
	}
	mvwprintw(iw, *cursor += 2, INDENT, "Lives done: %d", nex->cyc.lives_done);
	ft_print_visual_winner(nex);
}

void	ft_print_visual_winner(t_world *nexus)
{
	t_window	*iw;

	if (!(nexus->visual->print_winner))
		return ;
	iw = nexus->visual->info_window;
	wattron(iw, \
	COLOR_PAIR(nexus->visual->colors[nexus->survivor->id % COLOR_PAIR_NUM]));
	mvwprintw(iw, \
	getmaxy(iw) - INDENT, INDENT, "Winner: %s", nexus->survivor->name);
	wattroff(iw, \
	COLOR_PAIR(nexus->visual->colors[nexus->survivor->id % COLOR_PAIR_NUM]));
}

void	ft_print_info(t_world *nex)
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
	if (nex->visual->active)
		mvwprintw(iw, 2, j, "%s", "** RUNNING **");
	else
		mvwprintw(iw, 2, j, "%s", "** PAUSED **");
	mvwprintw(iw, i += 2, j, "%s", HELLO_STRING);
	mvwprintw(iw, i += 2, j, "%s %d", "Cycle/second limit: ", \
											nex->visual->cycle_speed);
	mvwprintw(iw, i += 2, INDENT, "%s %d", "Carry: ", nex->visual->carries);
	ft_print_info_playes(nex, &i);
	mvwprintw(iw, i += 2, j, "%s %d", "CYCLE_TO_DIE: ", nex->cyc.cyc_to_die);
	mvwprintw(iw, i += 2, j, "%s %d", "CYCLE_DELTA: ", CYCLE_DELTA);
	mvwprintw(iw, i += 2, j, "%s %d", "NBR_LIVE: ", NBR_LIVE);
	mvwprintw(iw, i += 2, j, "%s %d", "MAX_CHECKS: ", MAX_CHECKS);
	wrefresh(iw);
	wattroff(iw, A_BOLD);
}

void	ft_print_bytes(t_window *aw, uint8_t p, size_t i, size_t x)
{
	char	temp[2];

	temp[0] = p / 16;
	if (temp[0] > 9)
		temp[0] = temp[0] + 'a' - 10;
	else
		temp[0] = temp[0] + '0';
	temp[1] = p % 16;
	if (temp[1] > 9)
		temp[1] = temp[1] + 'a' - 10;
	else
		temp[1] = temp[1] + '0';
	mvwprintw(aw, i + 1, x, "%c%c", temp[0], temp[1]);
}

void	ft_print_ncursus_arena(t_world *nexus)
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
