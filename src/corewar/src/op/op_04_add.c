/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_04_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <mschimme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:22:49 by mschimme          #+#    #+#             */
/*   Updated: 2020/10/11 20:07:52 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

/*
!Контракт:
	*	Параметры, такие же как у всех остальных op-функций.
	*	По результатам работы должна модифицировать carry->exec_cyc, в 
		* соответствии с прочитанным и валидированным op-code.
	*	Должна модифицировать сarry->op = 0;
	*	Должна проитерировать указатель carry на арену:
		* если прочитан кривой op-code.
		* если инструкция исполнена корректно.
**	Function evaluates op-code read from arena (with VALID_OP_CODE macro) 
**	resulting carry->op == either op-code written in arena or == 0.
**	Op-code evaluated == 0 means nothing to do with current carry->pos(ition)
**	We iterate position on this occasion (by 1).
**	As finale we prepare to place our carry in queue of the next cycle.
*/

void		op_add(t_world *nexus, t_carry *carry, \
							t_dvasa *head, t_dvasa **vacant)
{
	t_op		op_cont;

	ft_clone_op_cont(14, &op_cont);
	if (!(ft_eval_operands_type(&nexus->arena[sizeof(RTP)], carry->pos, \
																	&op_cont)))
	{
		ft_get_operands(&nexus->arena[sizeof(RTP)], carry->pos, &op_cont);
		// MIND MOD and INSTRUCTION LOGICS!
		ft_exec_shit();
	}
	else
		ft_eval_operands_length(&nexus->arena[sizeof(RTP)], carry->pos, \
																	&op_cont);
	carry->op = 0;
	carry->pos += op_cont.length;
}
