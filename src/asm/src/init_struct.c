/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 15:28:59 by andru196          #+#    #+#             */
/*   Updated: 2021/04/10 19:03:25 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	new_command(t_asmcont *cont, int command)
{
	cont->command_list[cont->cmd_count].cmnd_num = command;
	cont->command_list[cont->cmd_count].row = g_row;
	cont->cmd_count++;
	return (cont->cmd_count - 1);
}

t_label	*new_label_min(char *str)
{
	t_label	*rez;

	rez = malloc(sizeof(t_label));
	if (rez)
	{
		ft_bzero(rez, sizeof(t_label));
		ft_strcpy(rez->name, str);
	}
	return (rez);
}

t_label	*new_label(t_asmcont *cont, char *str)
{
	t_label	*rez;
	t_label	*tmp;

	rez = new_label_min(str);
	if (rez)
	{
		rez->dst = &cont->command_list[cont->cmd_count];
		rez->row = g_row;
		tmp = cont->label_list;
		while (tmp && tmp->next)
			tmp = tmp->next;
		if (tmp)
			tmp->next = rez;
		else
			cont->label_list = rez;
	}
	return (rez);
}

static inline void	add_lbl(char *lbl_name, t_asmcont *cont,
			t_cmnd_label_link *rez, t_label *tmp_pr)
{
	rez->label = new_label_min(lbl_name);
	if (tmp_pr)
		tmp_pr->next = rez->label;
	else
		cont->label_list = rez->label;
}

t_cmnd_label_link	*new_connect(t_asmcont *cont, int arg_n, char *lbl_name)
{
	t_label				*tmp;
	t_label				*tmp_pr;
	t_cmnd_label_link	*rez;

	if (!as((void **)&rez, ft_memalloc(sizeof(t_cmnd_label_link))))
		return (rez);
	rez->col = g_column;
	tmp_pr = cont->label_list;
	tmp = NULL;
	if (tmp_pr)
		tmp = tmp_pr->next;
	while (tmp && ft_strcmp(tmp_pr->name, lbl_name)
		&& as((void **)&tmp_pr, tmp))
		tmp = tmp->next;
	if (tmp || (tmp_pr && !ft_strcmp(tmp_pr->name, lbl_name)))
		rez->label = tv(tmp && !ft_strcmp(tmp->name, lbl_name), tmp, tmp_pr);
	else
		add_lbl(lbl_name, cont, rez, tmp_pr);
	rez->arg_num = arg_n;
	rez->command = &cont->command_list[cont->cmd_count - 1];
	return (rez);
}
