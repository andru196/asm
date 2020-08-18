/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cor_command_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanya <tanya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 21:47:10 by andru196          #+#    #+#             */
/*   Updated: 2020/08/19 00:47:54 by tanya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern t_op		op_tab[OP_TAB_SIZE];

static int		is_finished(char *word)
{
	const char allowed[] = {' ', '\t'};

	while (*word)
	{
		if (*word == COMMENT_CHAR || *word == ALT_COMMENT_CHAR)
			return (1);
		if (!ft_charinstr(allowed, *word))
			return (0);
		word++;
	}
	return (1);
}

int				command_check(t_asmcont *cont, char *word, char **str, int len)
{
	int		i;
	int		new_c;
	int		j;
	int		shift;

	i = 0;
	while (i < OP_TAB_SIZE && op_tab[i].name && ft_strcmp(op_tab[i].name, word))
		i++;
	if (i == OP_TAB_SIZE || !op_tab[i].name)
		return (COMMAND_NOT_FOUND);
	g_column += len;
	new_c = new_command(cont, i);
	j = 0;
	ft_bzero(word, ft_strlen(word));
	while (j < op_tab[i].args_num)
	{
		skip_space(str);
		shift = cpy_arg_word(word, *str) + ft_strendwith(word, ",");
		*str += shift;
		if (!shift || args_check(cont, new_c, j++, word) == -1)
			return (ARGS_ERROR);
		g_column += shift;
	}
	return (!cpy_arg_word(word, *str) || is_finished(word) ? 1 : ARGS_ERROR);
}

int				digits_count(char *str)
{
	int i;

	i = 0;
	while (ft_isdigit(*str++))
		i++;
	return (i);
}
