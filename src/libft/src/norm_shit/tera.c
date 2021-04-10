/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tera.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 14:59:18 by sfalia-f          #+#    #+#             */
/*   Updated: 2021/04/10 15:01:07 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void				*tv(int bool_val, void *val1, void *val2)
{
	if (bool_val)
		return (val1);
	return (val2);
}

int					ti(int bool_val, int val1, int val2)
{
    if (bool_val)
        return (val1);
    return (val2);
}

char				tc(int bool_val, char val1, char val2)
{
    if (bool_val)
        return (val1);
    return (val2);
}

long				tl(int bool_val, long val1, long val2)
{
    if (bool_val)
        return (val1);
    return (val2);
}

unsigned			tu(int bool_val, unsigned val1, unsigned val2)
{
    if (bool_val)
        return (val1);
    return (val2);
}
