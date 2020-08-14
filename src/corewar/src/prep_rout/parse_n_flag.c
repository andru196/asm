/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_n_flag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 12:38:14 by mschimme          #+#    #+#             */
/*   Updated: 2020/07/14 12:58:15 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

/*
** Check ~/src/prep_rout/parse_fdump.c for hints.
*/

/*
* Проверил.
*/
inline static uint8_t	ft_register_fn_param(char *argv, long long *value, t_vasa **error_head)
{
	uint8_t				flag;

	flag = 0;
	if (ft_are_digits(argv))
	{
		*value = ft_atol_r(argv, &flag);
		if (_INT_OVF(*value) || flag || (*value > MAX_PLAYERS))
		{
			*value = -1;
			ft_err_fn_inter(error_head, argv);
			flag = 2;
		}
	}
	else
	{
		flag = 3;
		*value = -1;
		ft_err_fn_notnbr(error_head, argv);
	}
	return (flag);
}

/*
* Проверил.
*/
int				ft_get_n_flag(char ***argv, t_world *nexus)
{
	long long	res;
	uint8_t		flag;

	++*argv;																	// Итерируем, т.к. смотрим на -n, а нужно число.
	flag = ft_register_fn_param(**argv, &res, &nexus->errors);
	if (flag != 3)
		++*argv;
	return ((int)res);
}