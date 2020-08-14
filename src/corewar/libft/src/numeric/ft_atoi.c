/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 00:03:45 by mschimme          #+#    #+#             */
/*   Updated: 2020/04/26 15:50:28 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>


long long		ft_atol_r(const char *str, uint8_t *status)
{
	long long	res;
	int			sign;

	res = 0;
	if (!str)
	{
		*status = 1;
		return (res);
	}
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str += 1;
	sign = (*str == '-') * (-1) + (*str != '-');
	if (*str == '-' || *str == '+')
		str += 1;
	while (*str != '\0' && (*str >= '0' && *str <= '9'))
	{
		res = (res * 10) + (*str - '0');
		str += 1;
		if (res >= 223372036854775808 && *str == '9' && sign == -1)
			*status = 1;
		if (res > 223372036854775807 && *str == '9')
			*status = 2;
	}
	res *= sign;
	return (res);
}

int			ft_atoi(const char *str)
{
	long long	res;
	int			sign;

	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str += 1;
	sign = (*str == '-') ? -1 : 1;
	if (*str == '-' || *str == '+')
	{
		str += 1;
	}
	res = 0;
	while (*str != '\0' && (*str >= '0' && *str <= '9'))
	{
		res = (res * 10) + (*str - '0');
		str += 1;
		if (res >= 223372036854775808 && *str == '9' && sign == -1)
			return (0);
		if (res > 223372036854775807 && *str == '9')
			return (-1);
	}
	res *= sign;
	return (res);
}
