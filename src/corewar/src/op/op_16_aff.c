/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_16_aff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <mschimme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:22:49 by mschimme          #+#    #+#             */
/*   Updated: 2021/03/30 22:21:33 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

#define OP_CODE 16
/*
TODO:	ПЕРЕДЕЛАТЬ? Как эта хуйня вообще работать должна?..
*/
void		op_aff(t_world *nexus, t_carry *carry, \
							t_dvasa *head, t_dvasa **vacant)
{
	t_mop	op_cont;
	char	c;

	(void)head;
	(void)vacant;
	ft_clone_op_cont(OP_CODE, &op_cont);
	if (!(ft_eval_operands_type(&nexus->arena[sizeof(RTP)], carry->pos, \
									&op_cont, ft_get_op_cont(OP_CODE))))
	{
		ft_get_operands(&nexus->arena[sizeof(RTP)], &op_cont, carry, 1);
		c = (char)op_cont.operands[0];
		if (ft_isprint(c))
			write (1, &c, 1);
	}
	carry->op = 0;
	carry->pos += op_cont.length;
	carry->exec_cyc++;
}
