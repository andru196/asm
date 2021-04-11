/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_modes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <mschimme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 14:00:43 by mschimme          #+#    #+#             */
/*   Updated: 2021/04/11 16:07:43 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

void	ft_resolve_modes(t_world *nexus)
{
	uint8_t		flag;

	nexus->flags |= (NULL != nexus->cyc.cyc_to_dump);
	flag = nexus->flags;
	if ((flag & 3) > 2)
	{
		nexus->flags = 2;
		ft_err_both_modes(&nexus->errors, "-g and -dump flags confilct");
		ft_lstdel((t_list **)&(nexus->cyc.cyc_to_dump), NULL);
	}
}
