/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 15:59:01 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/01/26 17:06:16 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int main(int argc, char **argv)
{
	int	flag_mode;
	int error_code;

	if (argc < 2)
	{
		flag_mode = chaeck_flags(argv + 1, argc - 1, "-s");
		while (argc > 1)
			if (error_code = read_cor_file(argv[--argc], flag_mode))
				print_error(error_code);
	}
	else if (argc == 1)
		ft_printf("Usage: %s [-a] <sourcefile.s>\n", argv[0]);
	return (0);
}