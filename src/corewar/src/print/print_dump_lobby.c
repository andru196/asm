/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dump_lobby.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 22:30:43 by mschimme          #+#    #+#             */
/*   Updated: 2020/12/10 02:28:21 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

/*
TD	ДОПИСАТЬ вывод результата (и фсё);
TD:	Декларация - заглушка. Подобрать список нужных параметров.
!Контракт:
	*	Просто выводит состояние арены в текущий момент.
	*	Принимает указатель на указатель головы t_vasa, которые в своем 
	* ->gen.cyc_sol хранят циклы, в которые необхоимо дампнуться.
	*	Через голову управляет цепочкой дампов.
	*	Отпработав последний дамп-цикл должна подать сигнал на прерывание работы
	*	цикла (возвратить 1).


*/
uint8_t			ft_print_dump(t_world *nexus)
{
	t_vasa		*ptr;
	t_vasa		**cycle;
	char 		str[64 * 2 + 64];
	char 		*str_cpy;
	uint8_t		*bytes;

	cycle = &nexus->cyc.cyc_to_dump;
	ptr = *cycle;

	bytes = nexus->arena;
	size_t i = 0;
	size_t max = MEM_SIZE + sizeof(RTP) * 2;
	while (i < max)
	{
		str_cpy = str;
		ft_printf("%.8x:\t", i);
		do
		{
			uint8_t tmp = *bytes / 16;
			*str_cpy++ = tmp +  (tmp > 9 ? 'A' - 10 : '0');
			tmp = *bytes++ % 16;
			*str_cpy++ = tmp + (tmp > 9 ? 'A' - 10 : '0');
			*str_cpy++ = ' ';
			i++;
		} while ((i % 0x40) && i < max);
		str[64 * 2 + 63] = 0;
		ft_putendl(str);
	}
	ft_putendl("");
	*cycle = (*cycle)->next;
	ptr->gen.cyc_sol = 0;
	free(ptr);
	ptr = *cycle;
	return (*cycle == NULL);
}