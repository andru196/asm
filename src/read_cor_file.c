/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cor_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru196 <andru196@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 16:58:59 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/02/21 15:37:34 by andru196         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		cor_wordlen(char *str)
{
	int rez;

	rez = 0;
	while (*str && *str != ' ' && *str != '\t' && *str != COMMENT_CHAR
		&& *str != LABEL_CHAR && *str != DIRECT_CHAR && *str != SEPARATOR_CHAR)
	{
		rez++;
		str++;
	}
	return (rez);
}

static int 		cor_scan_word(t_asmcont *cont, char **str)
{
	char	word[MAX_WORD_LEN + 1];
	int		len;
	int		rez;

	len = cpy_word(word, *str);
	*str += len;
	rez = 0;
	if (*(str - 1) == LABEL_CHAR)
		rez = label_check(cont, word, len);
	if (!rez)
		rez = command_check(cont, word, str, len);
	if (!rez)
		rez = -1;
	return (rez);
}

static int		cor_scan(t_asmcont *cont, char *str)
{
	int		wlen;
	int		rez;
	t_row	row_data;

	rez = 0;
	str--;
	while (*(++str) && rez >= 0)
	{
		if (*str == ' ' || *str == '\t')
			continue ;
		else if (*str == COMMENT_CHAR || *str == ALT_COMMENT_CHAR)
			break ;
		rez = cor_scan_word(cont, &str);
	}
	return (rez);
}

static int		cor_read(int fd, t_asmcont *cont)
{
	int 	rez;
	char	*buf;

	cont->row = 0;
	while ((rez = get_next_line(fd, &buf)) > 0)
	{
		cont->row++;
		cont->col = 0;
		rez = cor_scan(cont, buf);
		ft_strdel(&buf);
		if (rez == -1)
			break ;
	}
	return (rez);
}

int		cor_open_file(char *file_name, int flag)
{
	int 		fd;
	int 		code;
	t_asmcont 	cont;

	code = 0;
	if (ft_strendwith(file_name, SOURCE_EXTENSION)) // подумать над lowercase
	{
		fd = open(file_name, O_RDONLY);
		if (fd != -1)
		{
			init_container(&cont);
			code = cor_read(fd, &cont);
			close(fd);
			code = asm_translate(&cont, file_name);
			free_asm_data(&cont);
		}
		else
			code = OPEN_FILE_ERROR; 
	}
	else
		code = SOURCE_EXTENSION_ERROR;
	return (code);
}
