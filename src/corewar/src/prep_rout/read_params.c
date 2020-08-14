/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 17:44:49 by mschimme          #+#    #+#             */
/*   Updated: 2020/07/20 23:22:27 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

/*
** //? В процессе проверки.
*/
uint8_t		ft_scan_lines(char ***argv, t_world *nexus, int *champ_count)
{
	if (**argv)
	{
		if (!ft_strcmp(**argv, "-dump"))
			return (ft_parse_fdump(argv, nexus, champ_count));
		else if (!ft_strcmp(**argv, "-n"))
				return (ft_parse_champ(argv, champ_count, ft_get_n_flag(argv, nexus), nexus));
		else if (!ft_strcmp(**argv, "-g"))										// Убрать, визуализацию не делаем.
			{
				(*argv)++;
				// ft_prep_visual(nexus);
			}
		else
		{
			return(ft_parse_champ(argv, champ_count, 0, nexus));
		}
	}
	return (0);
}

void		ft_read_params(char ***argv, t_world *nexus, int *champ_count)
{
	uint8_t	parse_stat;

	parse_stat = ft_scan_lines(argv, nexus, champ_count);
	if (ft_supervise_input(nexus, *champ_count))
		ft_manage_world(NULL);
}