/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gls_supp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <mschimme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 13:26:52 by mschimme          #+#    #+#             */
/*   Updated: 2019/11/22 14:04:33 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wipegnl(t_list **fdl, t_list *first, t_list *second, t_list *third)
{
	*fdl = NULL;
	(void)first;
	if (second)
		ft_lstdel(&second, ft_del);
	if (third)
		ft_lstdel(&third, ft_del);
	return (-1);
}
