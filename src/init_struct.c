/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru196 <andru196@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 15:28:59 by andru196          #+#    #+#             */
/*   Updated: 2020/02/02 16:37:09 by andru196         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	new_command(t_asmcont *cont, int command)
{
	cont->command_list[cont->cmd_count].cmnd_num = command;
	cont->cmd_count++;
	return (cont->cmd_count - 1);
}

t_label	*new_lable_min(char *str)
{
	t_label *rez;

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
	t_label *rez;
	t_label	*tmp;

	rez = new_lable_min(str);
	if (rez)
	{
		rez->dst = &cont->command_list[cont->cmd_count];
		rez->row = cont->row;
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


t_cmnd_label_link *new_connect(t_asmcont *cont, int arg_n, char *lbl_name)
{
	t_label 			*tmp;
	t_label				*tmp_pr;
	t_cmnd_label_link	*rez;

	rez = malloc(sizeof(t_cmnd_label_link));
	if (rez)
	{
		tmp_pr = cont->label_list;
		tmp = tmp_pr ? tmp_pr->next : NULL;
		while (tmp && ft_strcmp(tmp_pr->name, lbl_name))
			tmp = tmp->next;
		if (tmp || (tmp_pr && !ft_strcmp(tmp_pr->name, lbl_name)))
			rez->label = tmp ? tmp : tmp_pr;
		else
		{
			rez->label = new_label_min(lbl_name);
			if (tmp_pr)
				tmp_pr->next = rez->label;
			else
				cont->label_list = rez->label;
		}
		rez->arg_num = arg_n;
		rez->command = &cont->command_list[cont->cmd_count - 1];
	}
	return (rez);
}