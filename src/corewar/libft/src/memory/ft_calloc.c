/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <mschimme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 18:48:32 by mschimme          #+#    #+#             */
/*   Updated: 2019/12/08 15:59:15 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_calloc(size_t count, size_t size)
{
	size_t	total;
	void	*pocket;

	if (__builtin_umull_overflow(count, size, &total))
		return ((void *)(size_t)ft_err_varoverflow(__ERR(total), __func__) - 1);
	if (!(pocket = malloc(total)))
		return ((void *)(size_t)ft_err_malloc(__ERR(pocket), __func__) - 1);
	ft_bzero(pocket, total);
	return (pocket);
}
