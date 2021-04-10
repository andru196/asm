/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_12_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <mschimme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:22:49 by mschimme          #+#    #+#             */
/*   Updated: 2021/04/10 17:00:37 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

#define OP_CODE 12

/*
**	!Контракт:
**	Использует ft_dupe_carry для создания копии каретки.
**	Должна самостоятельно создавать контейнер t_vasa под новую каретку.
**	Обновляет положение указателя новой каретки.
**	Должна организовать помещение новой каректи в очередь на исполнение,
**	используя предусмотренную для этого ОБЩУЮ функцию.
*/

void	op_fork(t_world *nexus, t_carry *carry, \
							t_dvasa *head, t_dvasa **vacant)
{
	t_mop	op_cont;
	t_vasa	*vasa;

	vasa = NULL;
	ft_clone_op_cont(OP_CODE, &op_cont);
	ft_get_operands(&nexus->arena[sizeof(RTP)], &op_cont, carry, 1);
	vasa = (t_vasa *)ft_lstnew_r((void *)ft_dupe_carry(carry), sizeof(t_carry));
	if (!vasa || !(vasa->gen.carry))
	{
		if (*vacant)
			free(*vacant);
		ft_prox_err_malloc("new carry or its container", __func__);
	}
	vasa->gen.carry->pos += op_cont.operands[0] % op_cont.mod;
	carry->op = 0;
	if (nexus->flags & 2)
		++nexus->visual->carries;
	// ft_newcarry_place(vasa, head, vacant, &ft_add_offspring_by_id);
	ft_leafnode_pick(vasa, head, vacant, &ft_add_offspring_by_id);
	carry->pos += op_cont.length;
	update_visual_carry(carry, op_cont.length, nexus);
	carry->exec_cyc++;
}