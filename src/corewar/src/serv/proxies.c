/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proxies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <mschimme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 20:56:36 by mschimme          #+#    #+#             */
/*   Updated: 2021/04/10 17:04:29 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

int	ft_prox_err_ret(t_vasa **error_head, void *object, t_err_rout errfunc)
{
	errfunc(error_head, object);
	return (0);
}

void	ft_prox_err_malloc(const char *var, const char *par_func)
{
	ft_err_malloc((char *)var, par_func);
	ft_manage_world(NULL);
}
