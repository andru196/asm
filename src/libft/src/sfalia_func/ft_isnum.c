/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 21:59:37 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/08/15 01:03:01 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnumber(char *str)
{
	char	*cpy;

	if (!str || !*str)
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	if (!ft_strncmp("0x", str, 2) || !ft_strncmp("0X", str, 2))
		str += 2;
	cpy = str;
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (0);
		str++;
	}
	return (str != cpy);
}

long long	ft_maxint(unsigned char bytes, int unsig)
{
	long long   rez;

	unsig = !unsig;
	rez = 0;
	while (bytes--)
		rez |= 0xffL << ((bytes * 8) - (unsig ? unsig-- : 0));
	return (rez);
}
