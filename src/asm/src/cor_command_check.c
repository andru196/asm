/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cor_command_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 21:47:10 by andru196          #+#    #+#             */
/*   Updated: 2021/04/10 14:49:38 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern t_op	g_otab[OP_TAB_SIZE];

static int	is_finished(char *word)
{
	const char	allowed[] = {' ', '\t'};

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

static inline int	find_op(char *word)
{
	int	i ;

	i = 0;
	while (i < OP_TAB_SIZE && g_otab[i].name && ft_strcmp(g_otab[i].name, word))
		i++;
	return (i);
}

int	command_check(t_asmcont *cont, char *word, char **str, int len)
{
	int		i;
	int		new_c;
	int		j;
	int		shift;

	i = find_op(word);
	if (i == OP_TAB_SIZE || !g_otab[i].name)
		return (COMMAND_NOT_FOUND);
	g_column += len;
	new_c = new_command(cont, i);
	j = 0;
	ft_bzero(word, ft_strlen(word));
	while (j < g_otab[i].args_num)
	{
		skip_space(str);
		shift = cpy_arg_word(word, *str) + ft_strendwith(word, ",");
		*str += shift;
		if (!shift || args_check(cont, new_c, j++, word) == -1)
			return (ARGS_ERROR);
		g_column += shift;
	}
	if (!cpy_arg_word(word, *str) || is_finished(word))
		return (1);
	return (ARGS_ERROR);
}

int	digits_count(char *str)
{
	int	i;

	i = 0;
	while (ft_isdigit(*str++))
		i++;
	return (i);
}
