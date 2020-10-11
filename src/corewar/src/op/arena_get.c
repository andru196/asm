/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 11:56:10 by mschimme          #+#    #+#             */
/*   Updated: 2020/10/11 08:22:14 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

inline intptr_t	ft_calc_addr(intptr_t offset)
{
	return ((offset % MEM_SIZE) + MEM_SIZE * (offset < 0));
}

inline intptr_t	ft_step_size(uint8_t ops_type, uint8_t t_dir_size)
{
	return ((ops_type == T_REG) + (ops_type == T_DIR) * t_dir_size + \
												(ops_type == T_IND) * IND_SIZE);
}

inline uint8_t	ft_check_reg_is_valid(uint8_t *arena, uintptr_t ptr)
{
	uint8_t		value;

	value = arena[ft_calc_addr(ptr)];
	return (value > 0 && value <= REG_NUMBER);
}

/*
!Контракт:
	*	arena указывает на логическое начало арены (&nexus.arena[sizeof(RTP)]).
	*	offset не требует дополнительной нормализации (эксплуатация инлайна).
	*	перед логическим началом арены и за логическим концом арены должны быть
		* расположены '\0'-заполненные машинные слова sizeof(RTP).
*/
inline RTP		ft_get_bytecode(uint8_t *arena, intptr_t offset)
{
	offset = ft_calc_addr(offset);
	return (*(RTP *)(arena + offset) | \
			*(RTP *)(arena - sizeof(RTP) + \
						(((offset + sizeof(RTP)) % MEM_SIZE) * \
										((offset + sizeof(RTP)) / MEM_SIZE))));
}

inline void		ft_set_bytecode(uint8_t	*arena, intptr_t offset, RTP value, 
																uint8_t size)
{
	RTP			mask;

	offset = ft_calc_addr(offset);
	mask = 0xFFFFFFFFFFFFFFFFLU;
	value = ft_swap_endian(value, size);
	
}