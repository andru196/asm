/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 14:41:54 by mschimme          #+#    #+#             */
/*   Updated: 2020/07/20 19:59:48 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>
#define _FT_WIPE_CARRIES ft_lstdel
#define _FT_CLEAR_ERRORS ft_lstdel

/*
**	Временная функция ловить косяк, в случаях, если у нас и nexus пустой, и
**	guillotine задана жопой.
*/
static void ft_no_world(void)
{
	// DEBmesst("Проверяй, где облажался, ты пытаешься удалить арену (nexus), которую не задал!") DEBend()
	exit(1);
}


/*
**	//! В процессе написания.
**	We don't clear .desc as it is a part of .name.
*/
void	ft_wipe_champs(t_champ *ptr)
{
	DEBfunc()
	// DEBmesst("Функция по сути плейсхолдер. Проеряй, что аллочится под элементы чемпиона.")

	int				i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		DEBit(&ptr[i])
		if (ptr[i].body)
			free(ptr[i].body);
		// if (ptr[i].desc)
		// 	free(ptr[i].desc);
		if (ptr[i].name)
			free(ptr[i].name);
		ft_bzero((void *)&ptr[i], sizeof(t_champ));
		i++;
	}
	DEBend()
}

/*
**	//! В процессе написания.
*/
void	ft_manage_world(t_world *nexus)											//? МБ переработать параметры, добавить: void **, а также набор указателей для ft_lstdel
{
	// DEBfunc()
	// DEBmesst("Проверь, всё ли чистит. Написана ДО того, как определено содержимое структуры")
	// DEBmesst("Также учти, что используются стандартные функции удаления данных")
	// DEBend()
	static t_world *guillotine;

	if (nexus)
	{
		guillotine = nexus;
		return ;
	}
	else
	{
		if (guillotine)
		{
			_FT_WIPE_CARRIES((t_list **)&(guillotine->carry), &ft_del);
			ft_wipe_champs(&(guillotine->champ[0]));
			_FT_CLEAR_ERRORS((t_list **)&(guillotine->errors), &ft_del);
			guillotine->survivor = NULL;
		}
		else
			ft_no_world();
	}
	exit(0);
}
