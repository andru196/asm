/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_endian_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 08:23:43 by mschimme          #+#    #+#             */
/*   Updated: 2020/10/11 11:22:54 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

intptr_t		ft_calc_addr(intptr_t offset);


inline void		ft_set_bytecode(uint8_t	*arena, intptr_t offset, RTP value, 
																uint8_t size)
{
	RTP			mask;

	if (size > 4)
	{
		if (size < 7)
		{
			if (size == 5)
				mask = 0xFFFFFFFFFF;
		mask = 0xFFFFFFFFFFFF;
		}
		if (size == 7)
			mask = 0xFFFFFFFFFFFFFF;
		mask = 0xFFFFFFFFFFFFFFFF;
	}
	else if (size < 4)
	{
		if (size == 2)
			mask = 0xFFFF;
		if (size == 3)
			mask = 0xFFFFFF;
		mask = 0xFF;
	}
	else
		mask = 0xFFFFFFFF;
	value = ft_swap_endian(value, (uintptr_t)size);
	*(RTP *)arena |= mask;
	value =~ value;
	value 
		
}
int						main(void)
{
	RTP					source;
	int8_t				one_b;
	int16_t				two_b;
	int32_t				tri_b;
	int32_t				qua_b;
	int64_t				pen_b;
	int64_t				hex_b;
	int64_t				sep_b;
	int64_t				oct_b;

	uint8_t				buffer[8];

	ft_bzero(&buffer[0], sizeof(buffer));
	source = -5;
	one_b = two_b = tri_b = qua_b = pen_b = hex_b = sep_b = oct_b = source;
	buffer[3] = 0xAA;
	ft_set_bytecode(&buffer[0], 0, source, 3);
	
}