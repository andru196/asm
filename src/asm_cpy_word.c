/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_cpy_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru196 <andru196@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 21:28:58 by andru196          #+#    #+#             */
/*   Updated: 2020/02/09 21:34:30 by andru196         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int cpy_word(char *dst, char *src)
{
	int len;

	len = 0;
	while (len++ < MAX_WORD_LEN && *src != ' ' && *src != '\t' 
		&& *src != COMMENT_CHAR && *src != ALT_COMMENT_CHAR)
		*dst++ = *src++;
	*dst = '\0';
	return (len);
}
