/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cor_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru196 <andru196@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 16:58:59 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/02/02 21:43:12 by andru196         ###   ########.fr       */
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

static int 		cor_scan_label(t_asmcont *cont, char *str, int len)
{
	
}

static int 		cor_scan_cmd(t_asmcont *cont, char *str, int len)
{
	
}



static int		cor_scan(t_asmcont *cont, char **str)
{
	int		wlen;
	int		rez;
	t_row	row_data;

	rez = 0;
	while (**str == ' ' || **str == '\t')
	{	
		(*str)++;
		cont->col++;
	}
	if (!**str)
		return (0);
	ft_bzero(&row_data, sizeof(t_row));
/*
	Тут нужно определить что за слово перед нами
	смотрим не метка ли это, дальше не команда ли это, иначе кидаем ошибку
	Предполагается делать всё это в одном цикле, т.к. нужно исключить возникновение 2ух коман или меток
*/

	wlen = cor_wordlen(*str);
	if (*str && *(str + wlen) == LABEL_CHAR)
	{
		rez = cor_scan_label(cont, *str, wlen);
		*str += wlen + 1;
	}
	else if (*str)
	{
		rez = cor_scan_cmd(cont, *str, wlen);
		while (*str)
			str++;
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
		rez = cor_scan(cont, &buf);
		ft_strdel(&buf);
		if (rez == -1)
			break ;
	}
	return (rez);
}

// static int		cor_read(int fd, t_asmcont *cont)
// {
// 	int 	rez;
// 	char	buf[BUF_COR_SIZE + 1];
// 	char	*pnt;
// 	char	need_nl;

// 	cont->row = 0;
// 	cont->col = 0;
	
// 	ft_bzero(buf, BUF_COR_SIZE + 1);
// 	need_nl = 0;
// 	while ((rez = read(fd, buf, BUF_COR_SIZE)) > 0)
// 	{
// 		pnt = buf;
// 		while (--rez)
// 		{
// 			if (*pnt == '\n' && !(cont->col = 0)
// 				&& !(need_nl = 0))
// 				cont->row++;
// 			else
// 				cont->col++;
// 			need_nl = cor_scan(cont, &pnt);
// 			pnt++;
// 		}
// 		ft_bzero(buf, BUF_COR_SIZE + 1);
// 	}
// }

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
			cor_read(fd, &cont);
			close(fd);
		}
		else
			code = OPEN_FILE_ERROR;
	}
	else
		code = SOURCE_EXTENSION_ERROR;
	return (code);
}
