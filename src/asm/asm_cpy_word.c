/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_cpy_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru196 <andru196@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 21:28:58 by andru196          #+#    #+#             */
/*   Updated: 2020/03/09 21:37:54 by andru196         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	skip_space(char **str)
{
	int i;

	i = 0;
	while (**str == ' ' || **str == '\t')
	{
		(*str)++;
		i++;
	}
	g_column += i;
}

int		cpy_word(char *dst, char *src)
{
	int len;

	len = 0;
	while (len < MAX_WORD_LEN && *src != ' ' && *src != '\t' 
		&& *src != COMMENT_CHAR && *src != ALT_COMMENT_CHAR
		&& *src != SEPARATOR_CHAR && *src)
	{	
		len++;
		*dst++ = *src++;
	}
	if (*src == SEPARATOR_CHAR)
		*dst++ = *src++;		
	*dst = '\0';
	return (len);
}
