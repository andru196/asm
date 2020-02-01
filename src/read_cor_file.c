/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cor_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 16:58:59 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/02/01 14:46:14 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		cor_wordlen(char *str)
{
	int rez;

	rez = 0;
	while (*str && *str != ' ' && *str != '\t' && *str != '\n' && *str != COMMENT_CHAR
		&& *str != LABEL_CHAR && *str != DIRECT_CHAR && *str != SEPARATOR_CHAR)
	{
		rez++;
		str++;
	}
	return (rez);
}

static int		cor_scan(int row, int *col, char **str)
{
	int wlen;

	if (**str == ' ' || **str == '\t')
		return (0);
	else
		wlen = cor_wordlen(*str);
	//проверяем что за слово и заносим либо в список меток, либо в список команд
	//либо выводим еррор
	// если нашли слово или метку двигаем указатель и счетчик
}

static int		cor_read(int fd)
{
	int 	row;
	int		col;
	int 	rez;
	char	buf[BUF_COR_SIZE + 1];
	char	*pnt;

	row = 0;
	col = 0;
	ft_bzero(buf, BUF_COR_SIZE + 1);
	while ((rez = read(fd, buf, BUF_COR_SIZE)) > 0)
	{
		pnt = buf;
		while (--rez)
		{
			if (*pnt == '\n' && !(col = 0))
				row++;
			else
				col++;
			cor_scan(row, &col, &pnt);
			pnt++;
		}
		ft_bzero(buf, BUF_COR_SIZE + 1);
	}
}

int		cor_open_file(char *file_name, int flag)
{
	int fd;
	int code;

	code = 0;
	if (ft_strendwith(file_name, SOURCE_EXTENSION)) // подумать над lowercase
	{
		fd = open(file_name, O_RDONLY);
		if (fd != -1)
		{
			cor_read(fd);
			close(fd);
		}
		else
			code = OPEN_FILE_ERROR;
	}
	else
		code = SOURCE_EXTENSION_ERROR;
	return (code);
}
