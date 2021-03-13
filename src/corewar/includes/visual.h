/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 21:18:52 by ycorrupt          #+#    #+#             */
/*   Updated: 2021/03/13 18:58:32 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef VISUAL_H
# include "cwr_defs.h"
# include <curses.h>

# define FIELD_HEIGTH 66
# define INFO_WIDTH 60
# define ARENA_WIDTH (64 * 3) + 3
# define INDENT 3
# define DEFAULT_COLOR 100
/*
** The program has 4 default colors, in case of encreasing number of 
** champions (>4), the numbers will repeate each other.
*/
# define MAGENTA_PAIR 1
# define BLUE_PAIR 2
# define YELLOW_PAIR 3
# define GREEN_PAIR 4
# define COLOR_PAIR_NUM 4

typedef struct s_visual		t_visual;

struct						s_visual
{
	WINDOW					*arena_window;
    WINDOW					*info_window;
    t_bool					active;
    int 					attribute_arena[MEM_SIZE];
};

/*
******************			visualize funcs:			************************
*/

t_visual		*ft_init_visual();
void			ft_print_info(t_world *nexus);
void			ft_init_attribute_arena(t_world *nexus);


#endif
