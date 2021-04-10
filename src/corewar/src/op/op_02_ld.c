/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_02_ld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:22:49 by mschimme          #+#    #+#             */
/*   Updated: 2021/03/17 21:00:31 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

#define OP_CODE 2

/*
TODO:	Test!
*/
void		op_ld(t_world *nexus, t_carry *carry, \
							t_dvasa *head, t_dvasa **vacant)
{
	t_mop	op_cont;

	(void)head;
	(void)vacant;
	ft_clone_op_cont(OP_CODE, &op_cont);
	if (!(ft_eval_operands_type(&nexus->arena[sizeof(RTP)], carry->pos, \
											&op_cont, ft_get_op_cont(OP_CODE))))
	{
		ft_get_operands(&nexus->arena[sizeof(RTP)], &op_cont, carry, \
													op_cont.ops_amount - 1);
		carry->reg[op_cont.operands[1]] = op_cont.operands[0];
		carry->carry_flag = (t_bool)(!carry->reg[op_cont.operands[1]]);
	}
	carry->op = 0;
	carry->pos += op_cont.length;
	update_visual_carry(carry, op_cont.length, nexus);
	carry->exec_cyc++;
}