/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_05_sub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <mschimme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:22:49 by mschimme          #+#    #+#             */
/*   Updated: 2020/10/11 17:37:17 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

/*
!Контракт:
	*	Параметры, такие же как у всех остальных op-функций.
	*	По результатам работы должна модифицировать carry->exec_cyc, в 
		* соответствии с прочитанным и валидированным op-code.
	*	Должна модифицировать carry->op соответствующим корректным прочитанным
		* с арены op-code.
	*	Должна проитерировать указатель carry на арену, если прочитан кривой
		* op-code.
**	Function evaluates op-code read from arena (with VALID_OP_CODE macro) 
**	resulting carry->op == either op-code written in arena or == 0.
**	Op-code evaluated == 0 means nothing to do with current carry->pos(ition)
**	We iterate position on this occasion (by 1).
**	As finale we prepare to place our carry in queue of the next cycle.
*/
void		op_sub(t_world *nexus, t_carry *carry, \
							t_dvasa *head, t_dvasa **vacant)
{
	(void)nexus;
	(void)carry;
	(void)head;
	(void)vacant;
}