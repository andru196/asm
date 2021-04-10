/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_connections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 00:06:11 by sfalia-f          #+#    #+#             */
/*   Updated: 2021/04/10 13:25:51 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	fuck_connections(t_asmcont *c)
{
	t_cmnd_label_link	*tmp;
	t_cmnd_label_link	*pre;
	int					i;

	pre = c->conn_list;
	while (pre)
	{
		tmp = pre;
		g_row = tmp->command->row;
		if (!tmp->label->dst)
		{
			g_column = tmp->col;
			return (-1);
		}
		i = 0;
		while (tmp->label->dst - i > tmp->command)
			tmp->command->arg[tmp->arg_num] += (tmp->command + i++)->size;
		while (tmp->label->dst - i < tmp->command)
			tmp->command->arg[tmp->arg_num] -= (tmp->command + --i)->size;
		pre = pre->next;
	}
	return (0);
}
