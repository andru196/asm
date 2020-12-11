/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dump_lobby.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 22:30:43 by mschimme          #+#    #+#             */
/*   Updated: 2020/12/11 13:56:57 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

/*
**	Просто выводит состояние арены в текущий момент.
**	Принимает указатель на указатель головы t_vasa, которые в своем
** ->gen.cyc_sol хранят циклы, в которые необхоимо дампнуться.
**	Через голову управляет цепочкой дампов.
**	Отпработав последний дамп-цикл должна подать сигнал на прерывание работы
**	цикла (возвратить 1).
*/

void			set_dumpline(char str[64 * 2 + 64], uint8_t **bytes, size_t *i,
																	size_t max)
{
	size_t	cpy;
	uint8_t	*bytes_cpy;
	uint8_t	tmp;

	cpy = *i;
	bytes_cpy = *bytes;
	ft_bzero(str, sizeof(char) * (64 * 3));
	while ((++cpy % 0x40) && cpy < max)
	{
		tmp = *bytes_cpy / 16;
		*str++ = tmp + (tmp > 9 ? 'A' - 10 : '0');
		tmp = *bytes_cpy++ % 16;
		*str++ = tmp + (tmp > 9 ? 'A' - 10 : '0');
		*str++ = ' ';
	}
	str[64 * 3 - 1] = 0;
	*bytes = bytes_cpy;
	*i = cpy;
}

uint8_t			ft_print_dump(t_world *nexus)
{
	t_vasa			*ptr;
	char			str[64 * 2 + 64];
	uint8_t			*bytes;
	size_t			i;
	const size_t	max = MEM_SIZE;

	i = 0;
	ptr = nexus->cyc.cyc_to_dump;
	bytes = nexus->arena + sizeof(RTP);
	while (i < max)
	{
		ft_printf("%.5x:\t", i);
		set_dumpline(str, &bytes, &i, max);
		ft_putendl(str);
	}
	ft_putendl("");
	nexus->cyc.cyc_to_dump = nexus->cyc.cyc_to_dump->next;
	ptr->gen.cyc_sol = 0;
	free(ptr);
	return (nexus->cyc.cyc_to_dump == NULL);
}
