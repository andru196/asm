/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16_op_aff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:22:49 by mschimme          #+#    #+#             */
/*   Updated: 2020/09/08 14:40:48 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

/*
TODO:	Сделать.
*/
void		op_aff(t_world *nexus, t_carry *carry, \
							t_dvasa *head, t_dvasa **vacant)
{
	t_op	op_cont;
	int		i;
	char	c;

	ft_clone_op_cont(14, &op_cont);
	if (!(ft_eval_operands_type(&nexus->arena[sizeof(RTP)], carry->pos, \
									&op_cont)))
	{
		ft_get_operands(&nexus->arena[sizeof(RTP)], carry->pos, &op_cont);
		c = (char)op_cont.operands[0];
	}
	else
		ft_eval_operands_length(&nexus->arena[sizeof(RTP)], carry->pos, \
									&op_cont);
	carry->op = 0;
	carry->pos += op_cont.length;
}
