/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_outro.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 19:33:07 by mschimme          #+#    #+#             */
/*   Updated: 2020/11/20 14:47:22 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

void	ft_print_outro(t_champ *surv)
{
	ft_printf("Contestant %d, \"%s\", has won!\n", surv->id, surv->name);
}
