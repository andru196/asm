/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 02:41:57 by ycorrupt          #+#    #+#             */
/*   Updated: 2021/04/10 16:41:48 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

inline static int	get_increased_speed(int cycle_speed, int delta)
{
	if (cycle_speed + delta >= MAX_SPEED)
		return (MAX_SPEED);
	else
		return (cycle_speed + delta);
}

inline static int	get_decreased_speed(int cycle_speed, int delta)
{
	if (cycle_speed - delta <= MIN_SPEED)
		return (MIN_SPEED);
	else
		return (cycle_speed - delta);
}

inline static void	perform_button_action(int ch, t_world *nexus, \
											t_dvasa **tree, t_dvasa **vacant)
{
	usleep(1000000 / nexus->visual->cycle_speed);
	if (ch == SINGLE_CYCLE_BUTTON && *tree)
	{
		ft_make_cycle(nexus, tree, vacant);
		nexus->visual->active = 0;
	}
	else if (ch == ACTIVE_BUTTON)
		nexus->visual->active = !nexus->visual->active;
	else if (ch == INCREASE_SPEED_10)
		nexus->visual->cycle_speed = \
		get_increased_speed(nexus->visual->cycle_speed, 10);
	else if (ch == DECREASE_SPEED_10)
		nexus->visual->cycle_speed = \
		get_decreased_speed(nexus->visual->cycle_speed, 10);
	else if (ch == INCREASE_SPEED_1)
		nexus->visual->cycle_speed = \
		get_increased_speed(nexus->visual->cycle_speed, 1);
	else if (ch == DECREASE_SPEED_1)
		nexus->visual->cycle_speed = \
		get_decreased_speed(nexus->visual->cycle_speed, 1);
}

inline static void	init_all_visual(t_world *nexus)
{
	nexus->visual = ft_init_visual();
	ft_init_a_arena(nexus);
	ft_print_info(nexus);
	ft_print_ncursus_arena(nexus);
}

void	ft_visualize_cycle(t_world *nexus, t_dvasa *tree)
{
	t_dvasa	*vacant;
	int		ch;

	init_all_visual(nexus);
	vacant = NULL;
	while (1)
	{
		ch = getch();
		if (ch == 27)
			break ;
		perform_button_action(ch, nexus, &tree, &vacant);
		if (!tree)
		{
			nexus->visual->active = 0;
			nexus->visual->print_winner = 1;
		}
		if (nexus->visual->active && tree)
			ft_make_cycle(nexus, &tree, &vacant);
		if (ch)
			ft_print_info(nexus);
	}
	ft_destroy_leaftree(&tree, &vacant);
	if (vacant)
		free(vacant);
	free_visual(&(nexus->visual));
}
