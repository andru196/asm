/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operands_head_get_comp.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <mschimme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 23:53:36 by mschimme          #+#    #+#             */
/*   Updated: 2021/04/09 21:48:11 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

RTP		ft_get_ind_val_sch(uint8_t *arena, t_mop *op_cont, \
										t_carry *carry, intptr_t pos)
{
	intptr_t	offset;

	(void)carry;
	offset = (intptr_t)ft_swap_endian(ft_get_bytecode(arena, pos), IND_SIZE);
	if (op_cont->mod)
		offset %= op_cont->mod;
	return (ft_swap_endian(ft_get_bytecode(arena, carry->pos + offset), \
																	IND_SIZE));
}
