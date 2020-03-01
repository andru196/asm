/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru196 <andru196@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 15:59:01 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/03/01 16:32:52 by andru196         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_error (int ercode)
{
	ft_printf("COMPILATION ERROR %d", ercode);
}


int main(int argc, char **argv)
{
	int	flag_mode;
	int error_code;

	if (argc < 2)
	{
		flag_mode = 1;//check_flags(argv + 1, argc - 1, "-s");
		while (argc > 1)
			if ((error_code = cor_open_file(argv[--argc], flag_mode)))
				print_error(error_code);
	}
	else if (argc == 1)
		ft_printf("Usage: %s [-a] <sourcefile.s>\n", argv[0]);
	return (0);
}