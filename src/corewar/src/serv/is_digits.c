/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_digits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <mschimme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 11:53:10 by mschimme          #+#    #+#             */
/*   Updated: 2021/04/10 21:13:44 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

/*
**	UNUSED
**	int	ft_are_ndigits(const char *start, const char *end)
**	{
**		int		i;
**		char	c;
**	
**		i = (int)start && (end < start);
**		if (!i)
**			return (0);
**		c = *start;
**		while ((start != end) && (c = *start++))
**			if (c < '0' || c > '9')
**				return (0);
**		return (1);
**	}
*/

int	ft_are_digits(const char *str)
{
	char	c;

	if (!str)
		return (0);
	c = *str;
	while (c)
	{
		if (c < '0' || c > '9')
			return (0);
		str++;
		c = *str;
	}
	return (1);
}
