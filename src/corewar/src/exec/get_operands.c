/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_operands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 21:46:40 by mschimme          #+#    #+#             */
/*   Updated: 2020/10/16 09:27:26 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

/*
!КОНТРАКТ:
	*	arena	- всегда логическая арена.
	*	pos 	- всегда указывает на "голову" инструкции на арене.
	*	op_cont	- всегда "клон" op-структуры с уже высчитаными типами операнд.
	!	не подлежит применению в aff!
	!	не подлежит применению в live!
	!	не подлежит применению в zjmp!
	!	не подлежит применению в fork!
	!	не подлежит применению в lfork!
*/

static RTP		ft_get_nil_value(uint8_t *arena, t_op *op_cont, \
										t_carry *carry, intptr_t pos)
{
	(void)arena;
	(void)op_cont;
	(void)carry;
	(void)pos;
	ft_printf("\n!!! We entered ft_get_nil_value somehow!!!'\n");
	return (0);
}

static RTP		ft_get_reg_num(uint8_t *arena, t_op *op_cont, \
										t_carry *carry, intptr_t pos)
{
	(void)op_cont;
	(void)carry;
	return ((RTP)(arena[ft_calc_addr(pos)] - 1));
}

static RTP		ft_get_dir_value(uint8_t *arena, t_op *op_cont, \
										t_carry *carry, intptr_t pos)
{
	(void)op_cont;
	(void)carry;
	return (ft_swap_endian(ft_get_bytecode(arena, pos), T_DIR));
}

static RTP		ft_get_ind_value(uint8_t *arena, t_op *op_cont, \
										t_carry *carry, intptr_t pos)
{
	intptr_t	offset;

	(void)carry;
	offset = (intptr_t)ft_swap_endian(ft_get_bytecode(arena, pos), IND_SIZE);
	if (op_cont->mod)
		offset %= op_cont->mod;
	return (ft_swap_endian(ft_get_bytecode(arena, pos + offset), DIR_SIZE));
}


/*
TD: ДОБАВТЬ ИСПРАВЛЕНИЕ!
	TD:	Если amount < op_cont->ops_amount, для оставшихся опернад нужно особое
		TD: поведение: если тип операнда - не регистр: игнорить.
		TD: если тип операнда - регистр: записать в значение операнда его номер.
*/
void			ft_get_operands(uint8_t *arena, t_op *op_cont, t_carry *carry, \
												intptr_t amount)
{
	uint8_t		i;
	intptr_t	pos;
	static t_get_operand_val_rout *arr[5] = { &ft_get_nil_value, \
										&ft_get_reg_num, &ft_get_dir_value, \
										&ft_get_nil_value, &ft_get_ind_value };

	pos = carry->pos + OPC_SIZE + OPCB_SIZE;
	i = UINT8_MAX;
	while (++i < amount)
	{
		op_cont->operands[i] = arr[op_cont->ops_types[i]](arena, op_cont, \
																	carry, pos);
		pos += op_cont->ops_length[i];
	}
}
