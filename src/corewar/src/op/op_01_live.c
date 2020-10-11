/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_01_live.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <mschimme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:22:49 by mschimme          #+#    #+#             */
/*   Updated: 2020/10/11 19:14:38 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

/*
*Задачи:
	?	Считать оп-код по текущему положеню указателя. Записать в carry->op его
		? значение, если верный; Передвинуть на 1 байт оффсет-указатель, если
		? неверный.
*/
void		op_live(t_world *nexus, t_carry *carry, \
							t_dvasa *head, t_dvasa **vacant)
{
	t_op		*op_cont;
	uint8_t		*arena;
	uintptr_t	offset;
	
	op_cont = ft_get_op_cont(1);
	arena = &nexus->arena[sizeof(RTP)];
	ft_eval_operands_type(&nexus->arena[sizeof(RTP)], carry->pos, &op_cont);
	offset = OPC_SIZE + op_cont->ops_length[0];
	op_cont->operands[0] = -(ft_swap_endian(\
		ft_get_bytecode(arena, carry->pos + OPC_SIZE), op_cont->ops_length[0]));
	if (op_cont->operands[0] > 0 && op_cont->operands[0] <= nexus->champs)
		if (nexus->champ_ord[op_cont->operands[0] - 1]->alive)
			nexus->champ_ord[op_cont->operands[0] - 1]->last_live_op = \
																carry->exec_cyc;
	carry->last_live_op = carry->exec_cyc++;
	carry->op = 0;
	carry->pos += offset;
}