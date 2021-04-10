/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <mschimme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 14:41:54 by mschimme          #+#    #+#             */
/*   Updated: 2021/04/10 21:16:26 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>
/*
**	FUCK NORME!
**	#define _FT_WIPE_CARRIES ft_lstdel
**	#define _FT_CLEAR_ERRORS ft_lstdel
**	#define _FT_CLEAR_DUMPS ft_lstdel
*/

/*
**	Временная функция ловить косяк, в случаях, если у нас и nexus пустой, и
**	guillotine задана жопой. 
*/

static void	ft_no_world(void)
{
	exit(1);
}

/*
**	We don't clear .desc as it is a part of .name.
*/

void	ft_wipe_champs(t_champ *ptr)
{
	int				i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (ptr[i].body)
			free(ptr[i].body);
		if (ptr[i].name)
			free(ptr[i].name);
		ft_bzero((void *)&ptr[i], sizeof(t_champ));
		i++;
	}
}

/*
**	!		В процессе написания.
**		Чистит чемпионов по новой схеме;
**		Чистит champ_ord.
**		Удалил очистку кареток:
**			_FT_WIPE_CARRIES((t_list **)&(guillotine->carry), &ft_del);
**	!		Если утечки - проверь, чистятся ли каретки.
*/

void	ft_manage_world(t_world *nexus)
{
	static t_world	*guillotine;

	if (nexus)
	{
		guillotine = nexus;
		return ;
	}
	else
	{
		if (guillotine)
		{
			ft_wipe_champs(&(guillotine->champ[0]));
			ft_lstdel((t_list **)&(guillotine->errors), &ft_del);
			ft_lstdel((t_list **)&(guillotine->cyc.cyc_to_dump), NULL);
			guillotine->survivor = NULL;
			if (guillotine->champ_ord)
				free(guillotine->champ_ord);
		}
		else
			ft_no_world();
	}
	exit(0);
}
