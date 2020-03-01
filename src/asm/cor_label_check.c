/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cor_label_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru196 <andru196@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 21:17:18 by andru196          #+#    #+#             */
/*   Updated: 2020/02/10 22:11:46 by andru196         ###   ########.fr       */
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

int		label_check(t_asmcont *c, char *word, int len)
{
	if (len > T_LAB)
		return (LABEL_SIZE_ERROR);
	*(word + --len) = '\0';
	if (!check_chars(word))
		return (LABEL_FORBIDDEN_CHAR);
	if (!new_label(c, word))
		return (MALLOC_ERROR);
	return (1);
}
