/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_translate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 15:38:53 by andru196          #+#    #+#             */
/*   Updated: 2020/08/19 00:12:56 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			zapisat(char *rez, char *file_name, int flag, size_t size)
{
	char	*file_name_cor;
	int		fd;

	file_name_cor = ft_strreplacelast(file_name, SOURCE_EXTENSION, ASM_OUT_EXTENSION);
	fd = open(file_name_cor, O_WRONLY | O_CREAT, 3 << 7);
	free(file_name_cor);
	if (!(flag & fl_stdout))
		write(fd, rez, size);
	else
		write(1, rez, size);
	close(fd);
	return (0);
}

int			asm_translate(t_asmcont *cont, char *file_name, int flag)
{
	char	*rez;
	size_t	size;

	if ((size = data_size(cont) + PROG_NAME_LENGTH + COMMENT_LENGTH + 4 * 4) > MEM_SIZE)
		return (PROGRAM_SIZE_LIMIT);
	if (fuck_connections(cont) < 0)
		return (CONNECTION_ERROR);
	if (!(rez = ft_strnew(size)))
		return (MALLOC_ERROR);
	if (0 > transofrm_data(cont, rez, size))
		return (-1);
	zapisat(rez, file_name, flag, size);
	free(rez);
	return (0);
}
