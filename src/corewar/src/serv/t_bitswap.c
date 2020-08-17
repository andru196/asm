/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_bitswap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 10:10:05 by mschimme          #+#    #+#             */
/*   Updated: 2020/07/01 09:09:50 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

/*
**	Naming is correct. This function is supposed to check if _SW_ENDIAN macro
**	returns correct result.
*/

/*
** //! Obsolete function.
*/
int32_t	bytecode_to_int32(const uint8_t *bytecode, size_t size)
{
	int32_t	result;
	t_bool	sign;
	int		i;
	int			k;
	k = *(int *)&bytecode[0];
	k = _SW_ENDIAN(k);


	result = 0;
	sign = (t_bool)(bytecode[0] & 0x80);
	i = 0;
	while (size)
	{
		if (sign)
			result += ((bytecode[size - 1] ^ 0xFF) << (i++ * 8));
		else
			result += bytecode[size - 1] << (i++ * 8);
		size--;
	}
	if (sign)
		result = ~(result);
	if (k != result)
	{
		write(1, "WE FUCKED! _SW_ENDIAN FAILED!\n", 31);
		exit (0);
	}
	return (result);
}