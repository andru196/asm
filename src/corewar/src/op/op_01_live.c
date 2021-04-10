/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_01_live.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:22:49 by mschimme          #+#    #+#             */
/*   Updated: 2021/04/07 20:42:08 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

#define OP_CODE 1

/*
**!КОНТРАКТ:
**	*	nexus	- указывает на валидную базовую структуру.
**	*	carry	- указывает на текущую каретку.
**	*	head	- указывает на "голову" древа очереди исполнения.
**	*	vacant	- указывает в итоге на вакантную ноду древа (если есть).
**	/////TD:Задачи:
**	/////?	Считать оп-код по текущему положеню указателя. Записать в
**	/////	? carry->op его значение, если верный; Передвинуть на 1 байт
**	/////	? оффсет-указатель, если неверный.
TD:	TEST!
*/

void		op_live(t_world *nexus, t_carry *carry, \
							t_dvasa *head, t_dvasa **vacant)
{
	t_mop		op_cont;
	RTP			id;
	t_champ		*champion;

	(void)head;
	(void)vacant;
	ft_clone_op_cont(OP_CODE, &op_cont);
	ft_get_operands(&nexus->arena[sizeof(RTP)], &op_cont, carry, 1);
	id = -(op_cont.operands[0]);
	if (id > 0 && id <= nexus->champs)
	{
		champion = nexus->champ_ord[id - 1];
		if (champion->alive)
		{
			champion->last_live_op = carry->exec_cyc;
			nexus->survivor = champion;
		}
	}
	carry->op = 0;
	carry->pos += op_cont.length;
	update_visual_carry(carry, op_cont.length, nexus);
	carry->last_live_op = carry->exec_cyc++;
	nexus->cyc.lives_done++;
}
