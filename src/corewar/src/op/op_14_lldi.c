/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_14_lldi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <mschimme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:22:49 by mschimme          #+#    #+#             */
/*   Updated: 2021/04/10 20:09:14 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

#define OP_CODE 14

/*
** WHY!?
*/

#ifdef CWR_SCH_MOD

void	op_lldi(t_world *nexus, t_carry *carry, \
							t_dvasa *head, t_dvasa **vacant)
{
	t_mop	op_cont;

	(void)head;
	(void)vacant;
	ft_clone_op_cont(OP_CODE, &op_cont);
	if (!(ft_eval_operands_type(&nexus->arena[sizeof(RTP)], carry->pos, \
											&op_cont, ft_get_op_cont(OP_CODE))))
	{
		ft_get_operands(&nexus->arena[sizeof(RTP)], \
									&op_cont, carry, op_cont.ops_amount - 1);
		carry->reg[op_cont.operands[2]] = ft_swap_endian(ft_get_bytecode(\
			&nexus->arena[sizeof(RTP)], carry->pos + (op_cont.operands[0] + \
											op_cont.operands[1])), DIR_SIZE);
		carry->carry_flag = (t_bool)(!carry->reg[op_cont.operands[2]]);
	}
	carry->op = 0;
	carry->pos += op_cont.length;
	carry->exec_cyc++;
}

#else

void	op_lldi(t_world *nexus, t_carry *carry, \
							t_dvasa *head, t_dvasa **vacant)
{
	t_mop	op_cont;

	(void)head;
	(void)vacant;
	ft_clone_op_cont(OP_CODE, &op_cont);
	if (!(ft_eval_operands_type(&nexus->arena[sizeof(RTP)], carry->pos, \
											&op_cont, ft_get_op_cont(OP_CODE))))
	{
		ft_get_operands(&nexus->arena[sizeof(RTP)], \
									&op_cont, carry, op_cont.ops_amount - 1);
		carry->reg[op_cont.operands[2]] = ft_swap_endian(ft_get_bytecode(\
			&nexus->arena[sizeof(RTP)], carry->pos + (op_cont.operands[0] + \
											op_cont.operands[1])), DIR_SIZE);
	}
	carry->op = 0;
	carry->pos += op_cont.length;
	update_visual_carry(carry, op_cont.length, nexus);
	carry->exec_cyc++;
}

#endif
