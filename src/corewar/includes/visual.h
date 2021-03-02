/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 21:18:52 by ycorrupt          #+#    #+#             */
/*   Updated: 2021/03/02 23:42:28 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef VISUAL_H
# include "cwr_defs.h"
# include <curses.h>

# define FIELD_HEIGTH 66
# define INFO_WIDTH 60
# define ARENA_WIDTH (64 * 3) + 3
# define INDENT 3

typedef struct s_visual		t_visual;

struct						s_visual
{
	WINDOW					*arena_window;
    WINDOW					*info_window;
    t_bool					active;
};

/*
******************			visualize funcs:			************************
*/

t_visual		*ft_init_field(t_world *nexus);
void			ft_print_info(t_world *nexus);


#endif
