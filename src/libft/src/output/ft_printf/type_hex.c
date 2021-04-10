/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_hex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 18:33:09 by kokeefe           #+#    #+#             */
/*   Updated: 2021/04/10 18:34:46 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Forbidden defs:
**	#define FHASH frm->hash
**	#define FPRECISION frm->precision
**	#define HEXRES buffs[0]
**	#define HEXSET buffs[1]
*/

/*
**	In any "place" function (dir type_funcs) there is the same sort of array,
**	where:
**	arr[0]	-	no length flags.
**	arr[1]	-	-hh- length flag.
**	arr[2]	-	-h- length flag.
**	arr[3]	-	-l- length flag.
**	arr[4]	-	-z- length flag.
**	arr[5]	-	-j- length flag.
**	arr[6]	-	-ll- length flag.
**	arr[7]	-	-L- length flag.
**	If unsupported length flag was given in frm string, a default tip should
**	be chosen.
*/

static t_extract_hex_rout	*ft_get_tip(uint8_t num)
{
	static t_extract_hex_rout	*array[8];

	if (!array[0])
	{
		array[0] = &ft_get_hex_default;
		array[1] = &ft_get_hex_short_short;
		array[2] = &ft_get_hex_short;
		array[3] = &ft_get_hex_long;
		array[4] = &ft_get_hex_long;
		array[5] = &ft_get_hex_long;
		array[6] = &ft_get_hex_long_long;
		array[7] = &ft_get_hex_long_cap;
	}
	return (array[num]);
}

inline static void	ft_printout(t_format *formstat, \
									t_fword *frm, char *res, char *bogey)
{
	size_t						dims[2];

	if (*res)
	{
		dims[0] = ft_strlen(res);
		dims[1] = dims[0];
		if (frm->filler == '0')
		{
			filling_mainbuf(res, 2, 0, formstat->fd);
			dims[1] -= 2;
			frm->ftp_width(formstat, frm, &dims[0], bogey);
		}
		else
			frm->ftp_width(formstat, frm, &dims[0], res);
	}
	else
	{
		dims[0] = ft_strlen(bogey);
		dims[1] = dims[0];
		frm->ftp_width(formstat, frm, &dims[0], bogey);
	}
}

uint8_t	ft_place_hexal(t_format *formstat, \
													t_fword *frm)
{
	char						*buffs[2];
	char						*bogey;
	char						*buff;

	if ((frm->flags))
		frm->filler = ' ';
	else
		frm->precision = 1;
	if (!as((void **)&buff, ft_memalloc(24UL + frm->precision + frm->hash * 2)))
		return (1);
	buffs[0] = buff + 1;
	buffs[1] = "0123456789abcdef";
	bogey = ft_get_tip(frm->length_t)(frm, &buffs[0]);
	if (!*(bogey + 1))
		frm->hash = 0;
	buffs[0] = buff;
	ft_memset((void *)(buffs[0] + 2), '0', bogey + 1 - (buffs[0] + 2));
	bogey = buffs[0] + 2;
	if (frm->hash && *bogey)
		*(short int *)buffs[0] = (short int)30768U;
	ft_printout(formstat, frm, buffs[0], bogey);
	free(buffs[0]);
	if (formstat->errflag)
		return (1);
	return (0);
}
