/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_right.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 22:06:19 by mschimme          #+#    #+#             */
/*   Updated: 2020/07/02 22:49:26 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define ADDMAX formstat->result + *max
#define BSIZE sizes[0]
#define CSIZE sizes[1]
#define WIDTH format->width

static inline void		ft_place_filler(int width, char *fillers, int fd)
{
	while ((width))
	{
		while (width > 8)
		{
			filling_mainbuf(fillers, 8, 0, fd);
			width -= 8;
		}
		filling_mainbuf(fillers, width, 0, fd);
		width = 0;
	}
}

static inline uint8_t	ft_check_limits(t_format *formstat, \
								int width, size_t *sizes)
{
	int					newres;
	int					max;

	newres = 0;
	if (sizes[0] > INT32_MAX)
		return (ft_err_varoverflow(__ERR(vari_strlen), __func__));
	max = (CSIZE < (size_t)width) * ((size_t)width + BSIZE - CSIZE) + \
											(CSIZE >= (size_t)width) * BSIZE;
	if (ft_check_add_ovf(&newres, formstat->result, max))
		return (ft_err_varoverflow(__ERR(ADDMAX), __func__));
	formstat->result = newres;
	return (0);
}

void					ft_width_right(t_format *formstat, t_fword *format, \
									size_t *dims, char *formatted_variative)
{
	size_t				sizes[2];
	char				arr[8];

	sizes[0] = dims[0];
	if (ft_wdetect((const char *)formatted_variative, sizes[0]))
		sizes[1] = ft_wstrlen((const char *)formatted_variative);
	else
		sizes[1] = sizes[0];
	if (ft_check_limits(formstat, WIDTH, &sizes[0]))
		formstat->errflag = 1;
	ft_memset(&arr[0], ' ', 8);
	if (formstat->errflag)
		return ;
	filling_mainbuf(formatted_variative, dims[1], 0, formstat->fd);
	ft_place_filler((WIDTH > (int)CSIZE) * (WIDTH - (int)CSIZE), &arr[0],
															formstat->fd);
}
