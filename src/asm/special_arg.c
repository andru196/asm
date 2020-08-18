/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanya <tanya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 23:22:34 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/08/19 00:33:20 by tanya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char			*ft_strjoinnl(char *s1, char *s2)
{
	char	*rez;
	char	*cpy;

	cpy = ft_strjoin(s1, "\n");
	rez = ft_strjoin(cpy, s2);
	free(cpy);
	return (rez);
}

static int			multy_line_arg(int fd, char **rez, size_t *size)
{
	char	*buf;
	char	*cpy;
	char	*rezcpy;
	int		gnl;
	int		frst;

	frst = 0;
	while ((gnl = get_next_line(fd, &buf)) > 0 && ++g_row)
	{
		rezcpy = *rez;
		if ((cpy = ft_strchr(buf, QUOTE_CHAR)))
			*cpy = '\0';
		*rez = ft_strjoinnl(*rez, buf);
		if (frst || frst++)
			free(rezcpy);
		free(buf);
		if (cpy)
		{
			*size = ft_strlen(*rez) - 1;
			return (0);
		}
	}
	ft_strdel(rez);
	return (1);
}

// Error (line 54): function special_arg has 27 lines
// Error (line 81): line has 92 characters
// Error (line 82): line has 90 characters

int					special_arg(t_asmcont *c, int dst, char **str, int fd)
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
	if (**str != '"' || (!(cpy = ft_strchr(*str + 1, QUOTE_CHAR))
		&& multy_line_arg(fd, str, &size)))
		return (NONE_QUOTE_ERROR);
	else if (**str == '"' && cpy)
		size = cpy - *str - 1;
	if (!(rez = ft_strnew(size)))
		return (MALLOC_ERROR);
	ft_memcpy(rez, *str + 1, size);
	g_column = size + (ft_strstr(*str, "\n") ?
		-(ft_strstrlst(*str, "\n") - *str + 1) : g_column + 2);
	if (ft_strchr(*str, '\n'))
		ft_strdel(str);
	else
		*str += size + 1 + !ft_strstr(*str, "\n");
	if (dst)
		return (ft_strlen(c->comment = rez) > COMMENT_LENGTH ? TOO_LONG_COMMENT_ERROR : 2);
	return (ft_strlen(c->champ_name = rez) > PROG_NAME_LENGTH ? TOO_LONG_NAME_ERROR : 2);
}
