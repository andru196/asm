/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtonum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 00:03:45 by mschimme          #+#    #+#             */
/*   Updated: 2020/08/16 13:57:32 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#define LI64MAX (INT64_MAX / 10)
#define LI32MAX (INT32_MAX / 10)
#define WILL_OVERFLOW(x, y) res > (x) || res == (x) && *str > (y)
#define WILL_UNDERFLOW(x, y) res > (x) || res == (x) && *str > (y)


long long		ft_atol_r(const char *str, uint8_t *status)
{
	long long	res;
	int			sign;

	res = 0;
	if (!str)
		return ((*status = 1) - 1);
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	sign = (*str == '-') * (-1) + (*str != '-');
	str += (*str == '-') + (*str == '+');
	while (*str != '\0' && (*str >= '0' && *str <= '9'))
	{
		if (sign == -1 && (WILL_UNDERFLOW(LI64MAX, '8')) && (*status = 1))
			break ;
		if (sign == 1 && (WILL_OVERFLOW(LI64MAX, '7')) && (*status = 2))
			break ;
		res = (res * 10) + (*str - '0');
		str += 1;
	}
	if (*status)
		return ((*status == 1) * INT64_MIN + (*status == 2) * INT64_MAX);
	res *= sign;
	return (res);
}

long long		ft_atoll(const char *str)
{
	long long	res;
	int			sign;

	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str += 1;
	sign = (*str == '-') ? -1 : 1;
	str += (*str == '-') + (*str == '+');
	res = 0;
	while (*str != '\0' && (*str >= '0' && *str <= '9'))
	{
		if (sign == -1 && (WILL_UNDERFLOW(LI64MAX, '8')))
			return (0);
		if (sign == 1 && (WILL_OVERFLOW(LI64MAX, '7')))
			return (-1);
		res = (res * 10) + (*str - '0');
		str += 1;
	}
	res *= sign;
	return (res);
}

int				ft_atoi(const char *str)
{
	long long	res;
	int			sign;

	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str += 1;
	sign = (*str == '-') ? -1 : 1;
	str += (*str == '-') + (*str == '+');
	res = 0;
	while (*str != '\0' && (*str >= '0' && *str <= '9'))
	{
		if (sign == -1 && (WILL_UNDERFLOW(LI32MAX, '8')))
			return (0);
		if (sign == 1 && (WILL_OVERFLOW(LI32MAX, '7')))
			return (-1);
		res = (res * 10) + (*str - '0');
		str += 1;
	}
	res *= sign;
	return (res);
}
