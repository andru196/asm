/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_visual.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 15:10:39 by ycorrupt          #+#    #+#             */
/*   Updated: 2021/04/08 00:17:29 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

void	free_visual(t_visual **visual)
{
	delwin((*visual)->arena_window);
	delwin((*visual)->info_window);
	endwin();
	free(*visual);
}
