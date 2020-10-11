/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_14_lldi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <mschimme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:22:49 by mschimme          #+#    #+#             */
/*   Updated: 2020/10/11 17:39:31 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

/*
!Контакт
	* 
*/
void			op_lldi(t_world *nexus, t_carry *carry, \
							t_dvasa *head, t_dvasa **vacant)
{
	t_op		op_cont;
	uintptr_t	offset;
	uint8_t		i;

	ft_clone_op_cont(14, &op_cont);
	if (!(ft_eval_operands_type(&nexus->arena[sizeof(RTP)], carry->pos, &op_cont)))
	{
		i = UINT8_MAX;
		offset = OPC_SIZE + OPCB_SIZE;
		while (++i < op_cont.ops_amount)
		{
			
		}
	// Распарсить параметры.
	// Выполнить операцию.
	// Передвинуть каретку.
	// Обновить exec_cyc.
	return ;
	}
	// Передвинуть каретку.
	// Обновить exec_cyc.
}