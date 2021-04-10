/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_length.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 18:07:39 by kokeefe           #+#    #+#             */
/*   Updated: 2021/04/10 18:27:52 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Forbidden defines:
**	#define INTCAST(x) *(short int *)x
**	#define SIGHT (formstat->sight)
**	#define FLEN format->length_t
**	#define MAXFLEN(x) (FLEN > x) * FLEN + (FLEN <= x) * x
*/

#define FLAG_HH 26728
#define FLAG_LL 27756

uint8_t	ft_flag_length_dummy(t_format *formstat)
{
	if (ft_memchr("hlLzj", *(formstat->sight), 5))
	{
		if ((*(short int *)(formstat->sight) == FLAG_HH) || \
								(*(short int *)(formstat->sight) == FLAG_LL))
			(formstat->sight) += 1;
		return (1);
	}
	return (0);
}

inline static void	ft_extra_length_flags(t_format *formstat, \
															t_fword *format)
{
	if (*(formstat->sight) == 'j')
		format->length_t = t8(format->length_t > 5, format->length_t, 5);
}

uint8_t	ft_flag_length(t_format *formstat, t_fword *format)
{
	if (ft_memchr("hlLzj", *(formstat->sight), 5))
	{
		if (*(short int *)((formstat->sight)) == FLAG_HH)
		{
			(formstat->sight) += 1;
			format->length_t = t8(format->length_t > 1, format->length_t, 1);
		}
		else if (*(short int *)((formstat->sight)) == FLAG_LL)
		{
			(formstat->sight) += 1;
			format->length_t = t8(format->length_t > 6, format->length_t, 6);
		}
		else if (*(formstat->sight) == 'l')
			format->length_t = t8(format->length_t > 3, format->length_t, 3);
		else if (*(formstat->sight) == 'h')
			format->length_t = t8(format->length_t > 2, format->length_t, 2);
		else if (*(formstat->sight) == 'L')
			format->length_t = t8(format->length_t > 7, format->length_t, 7);
		else if (*(formstat->sight) == 'z')
			format->length_t = t8(format->length_t > 4, format->length_t, 4);
		else
			ft_extra_length_flags(formstat, format);
		return (1);
	}
	return (0);
}
