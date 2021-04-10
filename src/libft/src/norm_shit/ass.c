/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ass.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 15:01:15 by sfalia-f          #+#    #+#             */
/*   Updated: 2021/04/10 15:05:54 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	as(void **dst, void *val)
{
	*dst = val;
	return (val && 1);
}

int	asi(int *dst, int val)
{
	*dst = val;
	return (val && 1);
}

int	asll(long long int *dst, long long int val)
{
	*dst = val;
	return (val && 1);
}

int	as_c(char *dst, char val)
{
	*dst = val;
	return (val && 1);
}

int	asu(unsigned *dst, unsigned val)
{
	*dst = val;
	return (val && 1);
}
