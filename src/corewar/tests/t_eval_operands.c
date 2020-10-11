/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_eval_operands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 16:56:37 by mschimme          #+#    #+#             */
/*   Updated: 2020/10/10 18:16:23 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr_op_defs.h>
/*
sh ./t_compiler.sh t_eval_operands "./src/op/op_cont.c ./src/op/arena_get.c"
*/

int			main(void)
{
	t_world	nexus;
	t_op	op_cont;

	ft_clone_op_cont(14, &op_cont);
	ft_bzero(&nexus, sizeof(nexus));
	nexus.arena[10 + sizeof(RTP)] = 0xE4;
	nexus.arena[15 + sizeof(RTP)] = 0x02;
	ft_eval_operands_type(&nexus.arena[0], 9, &op_cont);
	
}