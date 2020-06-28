/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_length.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <mschimme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 18:07:39 by kokeefe           #+#    #+#             */
/*   Updated: 2019/10/29 00:37:02 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define INTCAST(x) *(short int *)x
#define SIGHT (formstat->sight)
#define FLEN format->length_t
#define MAXFLEN(x) (FLEN > x) * FLEN + (FLEN <= x) * x
#define FLAG_HH 26728
#define FLAG_LL 27756

uint8_t					ft_flag_length_dummy(t_format *formstat)
{
	if (ft_memchr("hlLzj", *SIGHT, 5))
	{
		if ((INTCAST(SIGHT) == FLAG_HH) || (INTCAST(SIGHT) == FLAG_LL))
			SIGHT += 1;
		return (1);
	}
	return (0);
}

inline static void		ft_extra_length_flags(t_format *formstat, \
															t_fword *format)
{
	if (*SIGHT == 'j')
		format->length_t = MAXFLEN(5);
}

uint8_t					ft_flag_length(t_format *formstat, t_fword *format)
{
	if (ft_memchr("hlLzj", *SIGHT, 5))
	{
		if (INTCAST(SIGHT) == FLAG_HH)
		{
			SIGHT += 1;
			format->length_t = MAXFLEN(1);
		}
		else if (INTCAST(SIGHT) == FLAG_LL)
		{
			SIGHT += 1;
			format->length_t = MAXFLEN(6);
		}
		else if (*SIGHT == 'l')
			format->length_t = MAXFLEN(3);
		else if (*SIGHT == 'h')
			format->length_t = MAXFLEN(2);
		else if (*SIGHT == 'L')
			format->length_t = MAXFLEN(7);
		else if (*SIGHT == 'z')
			format->length_t = MAXFLEN(4);
		else
			ft_extra_length_flags(formstat, format);
		return (1);
	}
	return (0);
}
