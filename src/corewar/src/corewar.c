/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 17:38:48 by mschimme          #+#    #+#             */
/*   Updated: 2020/08/02 12:41:38 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

#define STR_SGSTN "Correct the value in op.h and recompile."
/*
**	We allocate common memory space for name and description fields of the
**	champion entry. Less mallocs - easy memory management.
**	We always allocate memory for all those vacant champion entries.
**	So, if we've failed to allocate for all of them, we'll return 1 in
**	return check.
*/

inline static uint8_t	ft_init_champs_r(t_world *nexus)
{
	int					i;

	i = 0;
	while ((i != MAX_PLAYERS) && \
			(nexus->champ[i].name = (char *)ft_memalloc(DESC_BLOCK + \
														(REG_SIZE + 1) * 2)))
	{
		nexus->champ[i].desc = nexus->champ[i].name + \
			(uintptr_t)(PROG_NAME_LENGTH + REG_SIZE + 1);
		i++;
	}
	if (i != MAX_PLAYERS)
		ft_prox_err_malloc(__ERR(CH_NAME), __func__);
	return (0);
}

/*
**	We don't use ft_init_champs_r return status as we either exit with malloc
**	error, or continue the run.
*/
inline static void		ft_init_world(t_world *nexus, int *champs)
{
	ft_bzero(nexus, sizeof(t_world));
	ft_manage_world(nexus);
	*champs = 0;
	ft_init_champs_r(nexus);
}

#ifdef NOMINAL_LAUNCH

int						main(int argc, char **argv)
{
	t_world				nexus;
	int					champs;
	
	ft_init_world(&nexus, &champs);
	nexus.progname = *argv;
	argv++;
	if (argc > 1)
	{
	//* Добавил...
		ft_read_params(&argv, &nexus, &champs);
		ft_prep_battle(&nexus, champs);
	}
	else
		ft_show_man();

	ft_manage_world(NULL);
	return (0);
}
#endif

#ifdef FAULT_LAUNCH
int						main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	ft_show_compconf();
	return (0);
}
#endif


