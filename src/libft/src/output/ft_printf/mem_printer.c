/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_printer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <mschimme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:45:34 by mschimme          #+#    #+#             */
/*   Updated: 2019/10/30 18:00:21 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void				ft_putsym(const unsigned char *addr)
{
	if (*addr >= 32 && *addr <= 126)
		filling_mainbuf((const char *)addr, 1, 0);
	else
		filling_mainbuf(".", 1, 0);
}

static void				print_hex(unsigned char c)
{
	char	buff[3];
	int		i;
	char	*system;

	buff[2] = '\0';
	system = "0123456789abcdef";
	i = 1;
	while (i >= 0)
	{
		buff[i] = system[c % 16];
		c /= 16;
		i--;
	}
	filling_mainbuf(buff, 2, 0);
}

static void				ft_filler(size_t i, size_t step)
{
	while (i < step)
	{
		filling_mainbuf("  ", 2, 0);
		if (i && (i % 2))
			filling_mainbuf(" ", 1, 0);
		i++;
	}
}

inline static void		ft_print_hexes(size_t *ctr, size_t size, \
													const unsigned char *addr)
{
	while ((*ctr % 16) && *ctr < size)
	{
		print_hex(addr[*ctr]);
		if (*ctr && (*ctr % 2))
			filling_mainbuf(" ", 1, 0);
		++*ctr;
	}
}

void					ft_printmem(const char *addr, size_t size, int fl)
{
	size_t				ctr;
	size_t				offset;
	size_t				step;

	(void)fl;
	if (!addr)
		return ;
	step = 0;
	while (step < size)
		step += 16;
	ctr = 0;
	while (ctr < size)
	{
		offset = ctr;
		print_hex(addr[ctr++]);
		ft_print_hexes(&ctr, size, (const unsigned char *)addr);
		if (ctr >= size)
			ft_filler(ctr, step);
		ft_putsym((const unsigned char *)&addr[offset++]);
		while ((offset % 16) && offset < size)
			ft_putsym((const unsigned char *)&addr[offset++]);
		filling_mainbuf("\n", 1, 0);
	}
}
