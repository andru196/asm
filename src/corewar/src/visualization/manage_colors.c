/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 23:08:37 by ycorrupt          #+#    #+#             */
/*   Updated: 2021/04/10 16:54:39 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

static short int	ft_get_color_num(short int fg, short int bg)
{
	return (fg << 3 | bg);
}

short int	ft_swap_colors(short int color_num)
{
	short	fg;
	short	bg;

	pair_content(color_num, &fg, &bg);
	return (COLOR_PAIR(ft_get_color_num(bg, fg)));
}

void	ft_init_colors(short *colors)
{
	static short int	c[5] = {COLOR_MAGENTA, COLOR_BLUE, \
								COLOR_YELLOW, COLOR_GREEN, COLOR_WHITE};
	int					i;

	i = 0;
	while (i < 5)
	{
		init_pair(ft_get_color_num(c[i], COLOR_BLACK), c[i], COLOR_BLACK);
		init_pair(ft_get_color_num(COLOR_BLACK, c[i]), COLOR_BLACK, c[i]);
		colors[i] = ft_get_color_num(c[i], COLOR_BLACK);
		++i;
	}
}
