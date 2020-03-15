/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_cpy_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru196 <andru196@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 21:28:58 by andru196          #+#    #+#             */
/*   Updated: 2020/03/15 17:18:12 by andru196         ###   ########.fr       */
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

int		cpy_arg_word(char *dst, char *src)
{
	int len;

	len = 0;
	while (len < MAX_WORD_LEN && *src != COMMENT_CHAR 
	&& *src != ALT_COMMENT_CHAR	&& *src != SEPARATOR_CHAR && *src)
	{
		len++;
		*dst++ = *src++;
	}
	if (*src == SEPARATOR_CHAR)
		*dst++ = *src++;		
	*dst = '\0';
	return (len);
}

static char skip_num(char **wrd, long long num)
{
	long long	pow;
	long long	tmp;

	while (ft_charinstr(" \t+-\v", **wrd))
		(*wrd)++;
	pow = 10;
	if (**wrd == '0' && *(*wrd + 1))
		pow = *(*wrd + 1) == 'x' || *(*wrd + 1) == 'X' ? 16 : 8;
	if (**wrd == '0' && pow == 10 && !num)
		return (*(++(*wrd)));
	*wrd += (pow % 8 == 0) + (pow == 16);
	while (num)
	{
		tmp = 1;
		while (num / tmp != (**wrd - '0') && tmp < num)
			tmp *= pow;
		if (num / tmp == (**wrd - '0'))
		{	
			num -= tmp * (**wrd - '0');
			(*wrd)++;
		}
		else
			return (-1);
	}
	return (num == 0 && (ft_charinstr(" \t+-\v", **wrd) || !**wrd) ? 0 : -1);
}

void	ast_strrtrim(char *word)
{
	char *cpy;

	if (!*word)
		return ;
	cpy = word;
	while (*word)
		word++;
	word--;
	while (cpy != word && ft_isspace(*word))
		*word-- = '\0';
}

void skip_first_part(char **word)
{
	if (**word == DIRECT_CHAR)
		(*word)++;
	if (**word == '-' || **word == '+')
		(*word)++;
	while (ft_isdigit(**word) && **word)
		(*word)++;
}

void	prepare_arg(char *word, long long *arg)
{
	long long rez;
	long long tmp;
	char *cpy;

	skip_first_part(&word);
	while (*word && *word != '+' && *word != '-')
		word++;
	if (!*word)
		return ;
	cpy = word;
	while (ft_isspace(*(cpy - 1)))
		cpy--;
	rez = 0;
	while (*word)
	{
		if (*word == '+')
			tmp = ft_atoix(word + 1);
		if (*word == '-')
			tmp = ft_atoix(word + 1);
		if (skip_num(&word, tmp) == -1)
			return ;
		rez += tmp;
	}
	*arg = rez;
	*cpy = '\0';
}
