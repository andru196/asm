/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 21:18:52 by ycorrupt          #+#    #+#             */
/*   Updated: 2021/04/08 23:19:21 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef VISUAL_H
# define VISUAL_H
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
# define BOLD_CYCLE				50
# define HELLO_STRING			"Hello to our cool (maybe) COREWAR!!!"

/*
** Buttons
*/

# define ACTIVE_BUTTON			' '
# define SINGLE_CYCLE_BUTTON	's'
# define INCREASE_SPEED_10		'r'
# define DECREASE_SPEED_10		'q'
# define INCREASE_SPEED_1		'e'
# define DECREASE_SPEED_1		'w'

/*
** Colors 
*/

# define DEFAULT_COLOR			4


typedef WINDOW					t_window;
typedef struct s_visual			t_visual;
typedef struct s_attribute		t_attribute;

/*
** .value consist of color and additional attributes
*/

struct							s_attribute
{
	int							value;
	int							bold_cycle;
};

struct							s_visual
{
	t_window					*arena_window;
    t_window					*info_window;
    t_bool						active;
	t_bool						print_winner;
    t_attribute					a_arena[MEM_SIZE];
	int							cycle_speed;
	short						colors[5];
};

/*
******************			visualize funcs:			************************
*/

t_visual			*ft_init_visual();
void				ft_print_info(t_world *nexus);
void				ft_init_a_arena(t_world *nexus);
void				update_visual_carry(t_carry *carry, intptr_t length, t_world *nexus);
void				color_bytecode(t_carry *carry, t_world *nexus, intptr_t offset);
unsigned long int	set_new_color(unsigned long result, int color);
void				ft_init_colors(short *colors);
short int			ft_swap_colors(short int color);
void				update_one_carry(intptr_t pos, t_world *nexus, t_bool del_carry);
void				update_attribute_arena(t_world *nexus);
void				free_visual(t_visual **visual);
short int			ft_get_color_num(short int fg, short int bg);
void				ft_print_visual_winner(t_world *nexus);


#endif
