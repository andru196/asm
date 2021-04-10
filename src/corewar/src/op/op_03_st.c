/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_03_st.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <mschimme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:22:49 by mschimme          #+#    #+#             */
/*   Updated: 2021/04/10 16:59:30 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

#define OP_CODE 3


/*
**	!Контракт:
**		*	Параметры, такие же как у всех остальных op-функций.
**		*	По результатам работы должна модифицировать carry->exec_cyc, в
**			* соответствии с прочитанным и валидированным op-code.
**		*	Должна модифицировать сarry->op = 0;
**		*	Должна проитерировать указатель carry на арену:
**			* если прочитан кривой op-code.
**			* если инструкция исполнена корректно.
**		*	НЕ меняет carry->carry_flag!
**	TD: TEST!
*/

void	op_st(t_world *nexus, t_carry *carry, \
							t_dvasa *head, t_dvasa **vacant)
{
	t_mop	op_cont;
	static t_set_operand_val_rout	*arr[5] = { &ft_set_nil_val,
											&ft_set_reg_val, &ft_set_dir_val,
											&ft_set_nil_val, &ft_set_ind_val };

	(void)head;
	(void)vacant;
	ft_clone_op_cont(OP_CODE, &op_cont);
	if (!(ft_eval_operands_type(&nexus->arena[sizeof(RTP)], carry->pos, \
											&op_cont, ft_get_op_cont(OP_CODE))))
	{
		ft_get_operands(&nexus->arena[sizeof(RTP)], &op_cont, carry, \
													op_cont.ops_amount - 1);
		arr[op_cont.ops_types[1]](&nexus->arena[sizeof(RTP)], &op_cont, carry, \
																	carry->pos);
		if (op_cont.ops_types[1] == 4)
			color_bytecode(carry, nexus, (intptr_t)(carry->pos + op_cont.operands[1]));
	}
	carry->op = 0;
	carry->pos += op_cont.length;
	update_visual_carry(carry, op_cont.length, nexus);
	carry->exec_cyc++;
}
