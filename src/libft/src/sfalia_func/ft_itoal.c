/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 22:48:26 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/08/14 23:04:05 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sfalif_libft.h"

char		*ft_itoal(long long n)
{
	char	*pocket;
	int		volume;

	volume = ft_numvol(n);
	if (!(pocket = ft_strnew(volume)))
		return (NULL);
	if (n == 0)
		*pocket = '0';
	if (n == -2147483648)
	{
		pocket[0] = '-';
		pocket[1] = '2';
		n = 147483648;
	}
	if (n < 0)
	{
		pocket[0] = '-';
		n *= -1;
	}
	ft_itoafill(pocket + volume - 1, n);
	return (pocket);
}