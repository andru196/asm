/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_cor_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru196 <andru196@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 13:08:33 by andru196          #+#    #+#             */
/*   Updated: 2020/02/02 16:11:55 by andru196         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	init_container(t_asmcont *cont)
{
	ft_bzero(cont, sizeof(t_asmcont));
	cont->command_list = ft_memalloc(SIZE(t_command, MAX_COMMANDS));
	return (!cont->command_list);
}
