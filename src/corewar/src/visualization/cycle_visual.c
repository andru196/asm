/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_visual.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 14:23:00 by ycorrupt          #+#    #+#             */
/*   Updated: 2021/04/10 15:57:56 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

inline static void	ft_cycle_control(t_world *nexus, \
											t_dvasa **tree, t_dvasa **vacant)
{
	t_cycle				*cyc_ptr;

	cyc_ptr = &nexus->cyc;
	if (cyc_ptr->cycle == cyc_ptr->next_check)
	{
		ft_tree_undertaker(nexus, tree, vacant, cyc_ptr);
		if (++cyc_ptr->num_of_checks == MAX_CHECKS || \
												cyc_ptr->lives_done >= NBR_LIVE)
		{
			cyc_ptr->cyc_to_die = (cyc_ptr->cyc_to_die - CYCLE_DELTA) * \
										(cyc_ptr->cyc_to_die >= CYCLE_DELTA);
			cyc_ptr->num_of_checks = 0;
		}
		cyc_ptr->next_check += cyc_ptr->cyc_to_die + (cyc_ptr->cyc_to_die == 0);
		cyc_ptr->lives_done = 0;
	}
}

inline static uint8_t	ft_eval_op_code_valid(uint8_t op_code)
{
	return ((op_code >= 0 && op_code < KNOWN_OPS) * op_code);
}

inline static void	ft_carry_process(t_world *nexus, t_dvasa **tree, \
															t_dvasa **new_node)
{
	static t_op_rout	*op_tab[KNOWN_OPS] = {&op_new_op, &op_live, &op_ld,
						&op_st, &op_add, &op_sub, &op_and, &op_or, &op_xor,
						&op_zjmp, &op_ldi, &op_sti, &op_fork, &op_lld, &op_lldi,
						&op_lfork, &op_aff};
	uint8_t				op_code;
	t_vasa				*carry_bogey;

	carry_bogey = (*tree)->gen.vasa;
	if (nexus->cyc.cycle == carry_bogey->gen.carry->exec_cyc)
	{
		while (carry_bogey)
		{
			carry_bogey->gen.carry->pos = \
									ft_calc_addr(carry_bogey->gen.carry->pos);
			(*tree)->gen.vasa = (*tree)->gen.vasa->next;
			op_code = ft_eval_op_code_valid(nexus->arena[sizeof(RTP) + \
												carry_bogey->gen.carry->pos]);
			op_tab[carry_bogey->gen.carry->op](nexus, \
									carry_bogey->gen.carry, *tree, new_node);
			ft_leafnode_pick(carry_bogey, *tree, new_node, \
													&ft_add_offspring_by_id);
			carry_bogey = (*tree)->gen.vasa;
		}
		ft_leafnode_vacate(tree, new_node);
	}
}

void	ft_make_cycle(t_world *nexus, t_dvasa **tree, t_dvasa **vacant)
{
	if (tree)
	{
		nexus->cyc.cycle++;
		ft_carry_process(nexus, tree, vacant);
		ft_cycle_control(nexus, tree, vacant);
		update_attribute_arena(nexus);
		ft_print_ncursus_arena(nexus);
	}
}
