/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_battle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 18:16:19 by mschimme          #+#    #+#             */
/*   Updated: 2020/08/02 11:41:11 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>
#define PTR_ST ptrs[0]
#define PTR_EN ptrs[1]

inline static t_list	**ft_build_buff_nt(t_list **head, size_t size)
{
	t_list				**arr_ptr;
	size_t				i;
	t_list				*bogey;

	bogey = *head;
	i = 0;
	arr_ptr = (t_list **)ft_memalloc((size + 1) * sizeof(t_list *));
	while (i != size)
	{
		arr_ptr[i++] = bogey;
		bogey = bogey->next;
	}
	return (arr_ptr);
}

/*
**	Function tested in t_arr_sort.c
*/
inline static void		ft_sort_dumps(t_list **head, size_t amount)
{
	t_list				**arr_ptr;

	if (!(arr_ptr = ft_build_buff_nt(head, amount)))
		ft_prox_err_malloc(__ERR(arr_ptr), "ft_build_buff");
	ft_srt_listarr_bubble(head, arr_ptr, amount, ft_cyc_left_grt_right);
	free(arr_ptr);
}

inline static void		ft_place_champs(t_world *nexus, int ch_amount)
{
	int					i;
	uintptr_t			entry_ptr;

	i = 0;
	entry_ptr = 0;
	while (i != ch_amount)
	{
		ft_memcpy((void *)&nexus->arena[entry_ptr], \
					(void *)nexus->champ[i].body, (size_t)nexus->champ[i].size);
		entry_ptr += MEM_SIZE / ch_amount;
		i++;
	}
}

void					ft_prep_battle(t_world *nexus, int champs)
{
	if (nexus->cyc.cyc_to_dunp)
		ft_sort_dumps((t_list **)&nexus->cyc.cyc_to_dunp, \
										nexus->cyc.cyc_to_dunp->content_size);
	ft_place_champs(nexus, champs);
}
