/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_06_and.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:22:49 by mschimme          #+#    #+#             */
/*   Updated: 2020/10/16 08:14:52 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

#define OP_CODE 6

/*
!Контракт:
	*	Параметры, такие же как у всех остальных op-функций.
	*	По результатам работы должна модифицировать carry->exec_cyc, в 
		* соответствии с прочитанным и валидированным op-code.
	*	Должна модифицировать carry->op соответствующим корректным прочитанным
		* с арены op-code.
	*	Должна проитерировать указатель carry на арену, если прочитан кривой
		* op-code.
**	Function evaluates op-code read from arena (with VALID_OP_CODE macro) 
**	resulting carry->op == either op-code written in arena or == 0.
**	Op-code evaluated == 0 means nothing to do with current carry->pos(ition)
**	We iterate position on this occasion (by 1).
**	As finale we prepare to place our carry in queue of the next cycle.
*/
void		op_and(t_world *nexus, t_carry *carry, \
							t_dvasa *head, t_dvasa **vacant)
{
	t_op	op_cont;
	int		i;

	ft_clone_op_cont(14, &op_cont);
	if (!(ft_eval_operands_type(&nexus->arena[sizeof(RTP)], carry->pos, \
									&op_cont)))
	{
		ft_get_operands(&nexus->arena[sizeof(RTP)], carry->pos, &op_cont);
		carry->reg[op_cont.operands[2] - 1]  = ft_swap_endian(
						op_cont.operands[0] & op_cont.operands[1], REG_SIZE);
		carry->carry_flag = !carry->carry_flag;
	}
	else
		ft_eval_operands_length(&nexus->arena[sizeof(RTP)], carry->pos, \
																	&op_cont);
	carry->op = 0;
	carry->pos += op_cont.length;
}
