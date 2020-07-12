/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 16:40:02 by mschimme          #+#    #+#             */
/*   Updated: 2019/11/30 15:13:10 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_strclr(char *s)
{
	size_t size;

	if (s)
	{
		size = ft_strlen(s);
		ft_bzero((void *)s, size);
	}
}