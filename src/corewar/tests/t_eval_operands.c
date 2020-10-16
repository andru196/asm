/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_eval_operands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 16:56:37 by mschimme          #+#    #+#             */
/*   Updated: 2020/10/16 21:15:05 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr_op_defs.h>
/*
sh ./t_compiler.sh t_eval_operands "./src/op/op_cont.c ./src/op/arena_get.c ./src/flip_endian/end_01_conv_1_4.c ./src/flip_endian/end_02_conv_5-8.c"
*/

int			main(void)
{
	t_world	nexus;
	t_op	op_cont;

	ft_clone_op_cont(14, &op_cont);
	ft_bzero(&nexus, sizeof(nexus));
	nexus.arena[10 + sizeof(RTP)] = 0xE4;
	nexus.arena[15 + sizeof(RTP)] = 0x02;
	nexus.arena[20 + sizeof(RTP)] = 0xFC;
	ft_eval_operands_type(&nexus.arena[0 + sizeof(RTP)], 9, &op_cont, ft_get_op_cont(14));
	ft_eval_operands_type(&nexus.arena[0 + sizeof(RTP)], 14, &op_cont, ft_get_op_cont(14));
	ft_eval_operands_type(&nexus.arena[0 + sizeof(RTP)], 19, &op_cont, ft_get_op_cont(14));
}