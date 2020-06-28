/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <mschimme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 17:22:22 by mschimme          #+#    #+#             */
/*   Updated: 2019/10/30 18:04:29 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define FWIDTH format->width
#define FERR formstat->errflag

uint8_t				ft_place_mem(t_format *formstat, t_fword *format)
{
	const void		*ptr;
	int				res;
	t_printer_rout	*printer;

	if (!(format->width))
		format->width = 8;
	ptr = (const void *)ft_get_mem(format);
	if ((!ptr))
	{
		ptr = (void *)"(null)\n";
		res = 7;
		printer = &filling_mainbuf;
		format->width = res;
	}
	else
	{
		printer = &ft_printmem;
		res = (FWIDTH / 16 + ((FWIDTH % 16) != 0)) * 41 + FWIDTH;
	}
	if (ft_check_add_ovf(&(formstat->result), formstat->result, res))
		return (FERR = ft_err_varoverflow(__ERR(formstat->result), __func__));
	printer((const char *)ptr, (size_t)format->width, 0);
	return (0);
}
