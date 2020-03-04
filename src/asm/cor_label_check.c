/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cor_label_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru196 <andru196@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 21:17:18 by andru196          #+#    #+#             */
/*   Updated: 2020/03/03 22:09:02 by andru196         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int check_chars(char *word)
{
	while (*word)
		if (!ft_charinstr(LABEL_CHARS, *word++))
			return (0);
	return (1);
}

static char	find_label(t_asmcont *c, char *word)
{
	t_label *tmp;

	tmp = c->label_list;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, word))
			break;
		tmp = tmp->next;
	}
	if (!tmp)
		return (0);
	tmp->dst = &c->command_list[c->cmd_count];
	tmp->row = c->row;
	return (1);
}

int		label_check(t_asmcont *c, char *word, int len)
{
	if (len > T_LAB)
		return (LABEL_SIZE_ERROR);
	*(word + --len) = '\0';
	if (!check_chars(word))
		return (LABEL_FORBIDDEN_CHAR);
	if (!find_label(c, word))
		if (!new_label(c, word))
			return (MALLOC_ERROR);
	return (1);
}
