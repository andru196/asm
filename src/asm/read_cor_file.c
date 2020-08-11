/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cor_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 16:58:59 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/08/11 23:53:14 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char			*ft_strjoinnl(char *s1, char *s2)
{
	char	*rez;
	char	*cpy;

	cpy = ft_strjoin(s1, "\n");
	rez = ft_strjoin(cpy, s2);
	free(cpy);
	return (rez);
}

int				multy_line_arg(int fd, char **rez, size_t *size)
{
	char	*buf;
	char	*cpy;
	char	*rezcpy;
	int		gnl;
	int		frst;

	frst = 0;
	while ((gnl = get_next_line(fd, &buf)) > 0 && ++g_row
		&& !(cpy = ft_strchr(buf, QUOTE_CHAR)))
	{	
		rezcpy = *rez;
		*rez = ft_strjoinnl(*rez, buf);
		if (frst)
			free(rezcpy);
		else
			frst++;
		free(buf);
	}
	if (gnl <= 0 && !cpy)
		return (1);
	else
	{
		rezcpy = *rez;
		*cpy = '\0';
		*rez = ft_strjoinnl(*rez, buf);
		*size = ft_strlen(*rez) - 1;
		free(rezcpy);
		free(buf);
		return (0);
	}
}

int				special_arg(t_asmcont *c, int dst, char **str, int fd)
{
	int		i;
	char	*cpy;
	char	*rez;
	size_t	size;

	i = 0;
	while ((*str)[i] == ' ' || (*str)[i] == '\t')
		i++;
	*str += i;
	g_column += i;
	if ((**str != '"' || !(cpy = ft_strchr(*str + 1, QUOTE_CHAR))) 
		&& multy_line_arg(fd, str, &size))
		return (NONE_QUOTE_ERROR);
	else if (**str == '"' && cpy)
		size = cpy - *str - 1;
	if (!(rez = ft_strnew(size)))
		return (MALLOC_ERROR);
	ft_memcpy(rez, *str + 1, size);
	g_column = size + (ft_strstr(*str, "\n") ? -(ft_strstrlst(*str, "\n") - *str + 1) : g_column + 2);
	*str += size + 1 + !ft_strstr(*str, "\n");
	if (dst)
		c->comment = rez;
	else
		c->champ_name = rez;
	return ((dst && size > COMMENT_LENGTH) 
		|| (!dst && size > CHAMP_MAX_SIZE) ? -1 : 2);
}

static int		cor_scan_word(t_asmcont *cont, char **str, int fd)
{
	char	word[MAX_WORD_LEN + 1];
	int		len;
	int		rez;

	skip_space(str);
	len = cpy_word(word, *str);
	*str += len;
	rez = 0;
	if ((!cont->champ_name && !ft_strcmp(word, NAME_CMD_STRING))
	|| (!cont->comment && !ft_strcmp(word, COMMENT_CMD_STRING)))
	{
		g_column += len;
		rez = special_arg(cont, ft_strcmp(word, NAME_CMD_STRING), str, fd); //то что в кавычках
	}
	else if (*(*str - 1) == LABEL_CHAR)
	{
		if ((rez = label_check(cont, word, len)) > 0)
			g_column += len;
	}
	if (!rez)
		rez = command_check(cont, word, str, len);
	if (!rez)
		rez = -1;
	return (rez);
}

static int		cor_scan(t_asmcont *cont, char *str, int fd)
{
	int		rez;
	char	*move;

	rez = 0;
	while (*str && rez >= 0)
	{
		move = str;
		skip_space(&str);
		if (!*str || *str == COMMENT_CHAR || *str == ALT_COMMENT_CHAR)
			break ;
		rez = cor_scan_word(cont, &str, fd);
		if (!*str || rez < 0)
			break ;
		if (move == str)
			str++;
	}
	return (rez);
}

static int		cor_read(int fd, t_asmcont *cont)
{
	int		rez;
	char	*buf;

	g_row = 0;
	while ((rez = get_next_line(fd, &buf)) > 0)
	{
		g_row++;
		g_column = 0;
		rez = cor_scan(cont, buf, fd);
		ft_strdel(&buf);
		if (rez < 0)
			break ;
	}
	while (rez < 0 && get_next_line(fd, &buf))
		ft_strdel(&buf);
	
	return (rez);
}

void			free_asm_data(t_asmcont *c)
{
	void *tmp;
	void *pre;

	if (c->champ_name)
		free(c->champ_name);
	c->champ_name = NULL;
	if (c->comment)
	free(c->comment);
	c->comment = NULL;
	free(c->command_list);
	tmp = c->label_list;
	pre = tmp;
	while (tmp)
	{
		tmp = ((t_label *)tmp)->next;
		free(pre);
		pre = tmp;
	}
	c->label_list = NULL;
}

int				cor_open_file(char *file_name, int flag)
{
	int			fd;
	int			code;
	t_asmcont	cont;

	code = 0;
	g_column = 0;
	g_row = 0;
	if (ft_strendwith(file_name, SOURCE_EXTENSION)
		|| ft_strendwith(file_name, SOURCE_UPEXTENSION))
	{
		if ((fd = open(file_name, O_RDONLY)) != -1)
		{
			init_container(&cont);
			code = cor_read(fd, &cont);
			close(fd);
			if (code >= 0)
				code = asm_translate(&cont, file_name, flag);
			free_asm_data(&cont);
		}
		else
			code = OPEN_FILE_ERROR;
	}
	else
		code = SOURCE_EXTENSION_ERROR;
	return (code);
}
