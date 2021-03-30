/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_attributes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 21:46:49 by ycorrupt          #+#    #+#             */
/*   Updated: 2021/03/30 21:47:09 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

void		update_attribute_arena(t_world *nexus)
{
	int			i;
	t_attribute	*a_arena;

	a_arena = nexus->visual->a_arena;
	i = MEM_SIZE;
	while (--i >= 0)
	{
		if (a_arena[i].bold_cycle != 0)
		{
			--a_arena[i].bold_cycle;
			if (a_arena[i].bold_cycle == 0)
				a_arena[i].value = a_arena[i].value ^ A_BOLD;
		}
	}
}
