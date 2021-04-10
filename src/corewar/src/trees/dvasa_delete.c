/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dvasa_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <mschimme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 19:57:15 by mschimme          #+#    #+#             */
/*   Updated: 2021/04/10 21:36:49 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

/*
**	ПРОВЕРИЛ!
*/
void	ft_destroy_leaftree(t_dvasa **aleaf, t_dvasa **vacant)
{
	if (!aleaf)
		return ;
	if (vacant && *vacant)
		ft_del_leafnode(vacant);
	while (*aleaf)
	{
		ft_lstdel((t_list **)&((*aleaf)->gen.vasa), &ft_del);
		ft_del_leafnode(aleaf);
	}
}

/*
**	ПРОВЕРИЛ! В текущей версии.
**	КОНТРАКТ:
**	Не должна проверять наличие содержимого *tree, так как к моменту вызова
**	этой функции, лифнода текущего цикла должна быть априори пустой.
**	Должна прверять наличие валидного *tree для работы, т.к.
**	Здесь должна быть проверка на пустоту *tree (?)
**	Suggestion не подходит, т.к. мы в таком случае не переходим на 
**		следующий цикл.
*/
void	ft_leafnode_vacate(t_dvasa **tree, t_dvasa **vacant)
{
	t_dvasa	*sub;

	if (!(*tree))
		return ;
	if (!(*vacant))
	{
		*vacant = *tree;
		*tree = (*tree)->right.du_vasa;
		ft_bzero((void *)*vacant, sizeof(t_dvasa));
	}
	else
	{
		sub = *tree;
		*tree = (*tree)->right.du_vasa;
		free(sub);
	}
}

/*
**	ПРОВЕРИЛ!
*/
void	ft_del_leafnode(t_dvasa **aleaf)
{
	t_dvasa	*ptr;

	if (!aleaf)
		return ;
	if (*aleaf)
	{
		ptr = *aleaf;
		(*aleaf) = (*aleaf)->right.du_vasa;
		free(ptr);
	}
}
