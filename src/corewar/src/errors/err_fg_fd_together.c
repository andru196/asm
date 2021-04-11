/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_fg_fd_together.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <mschimme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 14:18:01 by mschimme          #+#    #+#             */
/*   Updated: 2021/04/11 14:23:56 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cwr.h>

#define FDFG_ERR1 "Both -dump and -g flags given. Will perform -g flag only."

void	ft_err_both_modes(t_vasa **head, void *object)
{
	t_vasa	*current;
	t_error	*error;

	error = (t_error *)ft_memalloc(sizeof(t_error));
	if (!error)
	{
		ft_err_malloc("error", __func__);
		ft_manage_world(NULL);
	}
	current = *head;
	error->argv_tar = (char *)object;
	error->errmessage = FDFG_ERR1;
	ft_lstadd((t_list **)head, ft_lstnew_r(error, sizeof(t_error)));
	if (*head == current)
	{
		ft_err_malloc("new_head", "ft_lstnew_r");
		free(error);
		error = NULL;
		ft_manage_world(NULL);
	}
}
