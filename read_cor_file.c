/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cor_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 16:58:59 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/01/26 17:38:24 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				read_cor_file(char *file_name, int flag)
{
	int fd;
	int code;

	code = 0;
	if (ft_strendwith(file_name, SOURCE_EXTENSION)) // подумать над lowercase
	{
		fd = open(file_name, O_RDONLY);
		if (fd != -1)
		{
			some_action();
			close(fd);
		}
		else
			code = OPEN_FILE_ERROR;
	}
	else
		code = SOURCE_EXTENSION_ERROR;
	return (code);
}
