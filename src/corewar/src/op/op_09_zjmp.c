/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_09_zjmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <mschimme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:22:49 by mschimme          #+#    #+#             */
/*   Updated: 2021/04/10 20:20:08 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

#define OP_CODE 9
/*
**	TODO:	Сделать.
*/
void	op_zjmp(t_world *nexus, t_carry *carry, \
							t_dvasa *head, t_dvasa **vacant)
{
	t_mop	op_cont;

	(void)head;
	(void)vacant;
	ft_clone_op_cont(OP_CODE, &op_cont);
	if (carry->carry_flag)
	{
		ft_get_operands(&nexus->arena[sizeof(RTP)], &op_cont, carry, 1);
		carry->pos += (op_cont.operands[0] % op_cont.mod);
		update_visual_carry(carry, op_cont.operands[0] % op_cont.mod, nexus);
	}
	else
	{
		carry->pos += op_cont.length;
		update_visual_carry(carry, op_cont.length, nexus);
	}
	carry->op = 0;
	carry->exec_cyc++;
}
