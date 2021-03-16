/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 23:08:37 by ycorrupt          #+#    #+#             */
/*   Updated: 2021/03/17 00:19:30 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

short int	ft_swap_colors(short int color)
{
	short int temp;

	temp = color << 4;
	return (temp | color >> 4);
}

short int	ft_get_color_num(short int fg, short int bg)
{
    return (fg << 4 | bg);
}

void	ft_init_colors(int *colors)
{
	init_pair(ft_get_color_num(COLOR_WHITE, COLOR_BLACK), COLOR_WHITE, COLOR_BLACK);
	init_pair(ft_get_color_num(COLOR_MAGENTA, COLOR_BLACK), COLOR_MAGENTA, COLOR_BLACK);
	init_pair(ft_get_color_num(COLOR_BLUE, COLOR_BLACK), COLOR_BLUE, COLOR_BLACK);
	init_pair(ft_get_color_num(COLOR_YELLOW, COLOR_BLACK), COLOR_YELLOW, COLOR_BLACK);
	init_pair(ft_get_color_num(COLOR_GREEN, COLOR_BLACK), COLOR_GREEN, COLOR_BLACK);
	init_pair(ft_get_color_num(COLOR_BLACK, COLOR_WHITE),COLOR_BLACK, COLOR_WHITE);
	init_pair(ft_get_color_num(COLOR_BLACK, COLOR_MAGENTA), COLOR_BLACK, COLOR_MAGENTA);
	init_pair(ft_get_color_num(COLOR_BLACK, COLOR_BLUE), COLOR_BLACK, COLOR_BLUE);
	init_pair(ft_get_color_num(COLOR_BLACK, COLOR_YELLOW), COLOR_BLACK, COLOR_YELLOW);
	init_pair(ft_get_color_num(COLOR_BLACK, COLOR_GREEN), COLOR_BLACK, COLOR_GREEN);
	colors[0] = COLOR_PAIR(ft_get_color_num(COLOR_MAGENTA, COLOR_BLACK));
	colors[1] = COLOR_PAIR(ft_get_color_num(COLOR_BLUE, COLOR_BLACK)),
	colors[2] = COLOR_PAIR(ft_get_color_num(COLOR_YELLOW, COLOR_BLACK)),
	colors[3] = COLOR_PAIR(ft_get_color_num(COLOR_GREEN, COLOR_BLACK));
	colors[4] = COLOR_PAIR(ft_get_color_num(COLOR_WHITE, COLOR_BLACK));
}
