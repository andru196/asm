/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 21:18:52 by ycorrupt          #+#    #+#             */
/*   Updated: 2021/03/16 22:44:07 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef VISUAL_H
# include "cwr_defs.h"
# include <curses.h>
# include <time.h>

/*
** General
** COLOR_PAIR_NUM - a number of color pairs. In case of encreasing number of 
** champions (>4), the numbers will repeate each other.
*/

# define FIELD_HEIGTH			66
# define INFO_WIDTH				60
# define ARENA_WIDTH			(64 * 3) + 3
# define INDENT					3
# define COLOR_PAIR_NUM			4
# define MAX_SPEED				1000
# define MIN_SPEED				1

/*
** Buttons
*/

# define ACTIVE_BUTTON			' '
# define SINGLE_CYCLE_BUTTON	's'
# define INCREASE_SPEED_100		'y'
# define DECREASE_SPEED_100		'q'
# define INCREASE_SPEED_10		't'
# define DECREASE_SPEED_10		'w'
# define INCREASE_SPEED_1		'r'
# define DECREASE_SPEED_1		'e'

/*
** Colors 
*/

# define DEFAULT_COLOR			100
# define MAGENTA_PAIR			1
# define BLUE_PAIR				2
# define YELLOW_PAIR			3
# define GREEN_PAIR				4
# define CARRIAGE_NUMBER		10
# define CARRIAGE_MAGENTA_PAIR	(MAGENTA_PAIR + CARRIAGE_NUMBER)
# define CARRIAGE_BLUE_PAIR		(BLUE_PAIR + CARRIAGE_NUMBER)
# define CARRIAGE_YELLOW_PAIR	(YELLOW_PAIR + CARRIAGE_NUMBER)
# define CARRIAGE_GREEN_PAIR	(GREEN_PAIR + CARRIAGE_NUMBER)


typedef struct s_visual		t_visual;

struct						s_visual
{
	WINDOW					*arena_window;
    WINDOW					*info_window;
    t_bool					active;
    unsigned long int	    attribute_arena[MEM_SIZE];
	unsigned long int       cycle_speed;
};

/*
******************			visualize funcs:			************************
*/

t_visual			*ft_init_visual();
void				ft_print_info(t_world *nexus);
void				ft_init_attribute_arena(t_world *nexus);
void				update_visual_carry(t_carry *carry, intptr_t length, t_world *nexus);
void				color_bytecode(t_carry *carry, t_world *nexus, intptr_t offset);
unsigned long int	set_new_color(unsigned long result, int color);


#endif
