/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 12:43:28 by mschimme          #+#    #+#             */
/*   Updated: 2021/04/10 20:31:22 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

inline static char	*ft_itoafill(char *endofpocket, long long int n)
{
	if (!n)
		*--endofpocket = n + 48;
	while (n)
	{
		*--endofpocket = (n % 10) + 48;
		n /= 10;
	}
	return (endofpocket);
}

/*
**		Some old function version.
**	inline static int		ft_numvol(long long int n)
**	{
**		size_t				v;
**		v = 0;
**		if (0 == n)
**			v++;
**		while (0 != n)
**		{
**			v++;
**			n /= 10;
**		}
**		return (v);
**	}
*/

inline static int	ft_numvol(long long int n)
{
	size_t				v;

	v = 0 + (n <= 0);
	while (n && ++v)
		n /= 10;
	return (v);
}

char	*ft_itoal(long long int num)
{
	size_t				volume;
	char				*pocket;

	volume = ft_numvol(num);
	if (!as((void **)&pocket, ft_strnew(volume)))
		return (NULL);
	if (num == INT64_MIN)
	{
		*(short int *)pocket = (short int)('-' + ('9' << 8));
		num = 223372036854775808LL;
	}
	if (num < 0)
	{
		*pocket = '-';
		num *= -1;
	}
	ft_itoafill(pocket + volume, num);
	return (pocket);
}
