/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwr.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <mschimme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 21:21:56 by mschimme          #+#    #+#             */
/*   Updated: 2021/04/08 22:08:15 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CWR_H
# define CWR_H
# include <libft.h>
# include <termios.h>
# include <op.h>
# include "op_lims.h"
# include "cwr_defs.h"
# include "cwr_funcs.h"
# include <curses.h>
# include <sys/ioctl.h>

# ifndef CWR_SCH_MOD
#  define CWR_SCH_MOD
# endif
/*
**	curses.h - для графического режима.
**	ioctl.h - для получения актуальных данных по состоянию терминала.
**	termios.h - для контроля терминального устройства, в т.ч. для очистки
**	машинописного буфера ввода.
*/

#endif
