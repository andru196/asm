/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_translate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru196 <andru196@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 15:38:53 by andru196          #+#    #+#             */
/*   Updated: 2020/02/24 13:26:20 by andru196         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern t_op *op_tab;

size_t	data_size(t_asmcont *c)
{
	size_t		rez;
	t_command	*cmd;
	int			cmd_size;
	size_t		i;
	int			j;

	rez = 0;
	i = -1;
	cmd = c->command_list;
	while (++i < c->cmd_count)
	{
		j = -1;
		cmd_size = 1 + op_tab[c->command_list[i].cmnd_num].args_types_code;
		while (++j < op_tab[c->command_list[i].cmnd_num].args_num)
		{
			if (c->command_list[i].arg_size[j] == T_REG)
				cmd_size += REG_SIZE;
			else if (c->command_list[i].arg_size[j] == T_IND)
				cmd_size += IND_SIZE;
			else
				cmd_size += DIR_SIZE / (op_tab[c->command_list[i].cmnd_num].t_dir_size + 1);
		}
		c->command_list[i].size = cmd_size;
	}
	return (rez);
}

int		fuck_connections(t_asmcont *c)
{
	t_cmnd_label_link *tmp;
	t_cmnd_label_link *pre;

	pre = c->conn_list;
	while (pre)
	{
		tmp = pre;
		if (!tmp->label->dst)
			return (-1);
		tmp->command->arg[tmp->arg_num] = tmp->label->dst - tmp->command;
		free(tmp);
		pre = pre->next;
	}
	return (0);
}

int		type_code(t_command *cmd)
{
	int rez;

	rez = 0;
	if (cmd->arg_size[0] == T_REG)
		rez |= REG_CODE << 6;
	else if (cmd->arg_size[0] == T_IND)
		rez |= IND_CODE << 6;
	else if (cmd->arg_size[0] == T_DIR)
		rez |= DIR_CODE << 6;

	if (cmd->arg_size[1] == T_REG)
		rez |= REG_CODE << 4;
	else if (cmd->arg_size[1] == T_IND)
		rez |= IND_CODE << 4;
	else if (cmd->arg_size[1] == T_DIR)
		rez |= DIR_CODE << 4;
	
	if (cmd->arg_size[2] == T_REG)
		rez |= REG_CODE << 4;
	else if (cmd->arg_size[2] == T_IND)
		rez |= IND_CODE << 4;
	else if (cmd->arg_size[2] == T_DIR)
		rez |= DIR_CODE << 4;
	return (rez);
}

void write_n_num(char **dst, long long n, unsigned char bytes)
{
	if (n >= 1 << bytes * 8)
		n %= 1 << bytes * 8 - 1;
	while (bytes)
	{
		**dst = *(char *)(&n + (sizeof(long long) - bytes--));
		(*dst)++;
	}
}

void	write_cmnd(char *dst, t_command *cmd)
{
	int	i;

	*dst++ = cmd->cmnd_num;
	if (op_tab[cmd->cmnd_num].args_types_code)
	{
		*(int *)dst = type_code(cmd);
		dst += sizeof(int);
	}
	i = 0;
	while (i < op_tab[cmd->cmnd_num].args_num)
	{
		if (cmd->arg_size[i] == T_REG)
			write_n_num(&dst, cmd->arg[i], REG_SIZE);
		else if (cmd->arg_size[i] == T_IND)
			write_n_num(&dst, cmd->arg[i], IND_SIZE);
		else if (cmd->arg_size[i] == T_DIR)
			write_n_num(&dst, cmd->arg[i], DIR_SIZE / (1 + op_tab[cmd->cmnd_num].t_dir_size));
	}
	
}

int		transofrm_data(t_asmcont *cont, char *rez, unsigned size)
{
	int			i;
	int			j;

	*(int *)rez = COREWAR_EXEC_MAGIC;
	i = 0 + sizeof(int);
	ft_strncpy(rez + i, cont->champ_name, PROG_NAME_LENGTH);
	i += PROG_NAME_LENGTH;
	*(int *)(rez + i) = 0;
	i += sizeof(int);
	*(int *)(rez + i) = size;
	i += sizeof(unsigned);
	ft_strncpy(rez + i, cont->comment, COMMENT_LENGTH);
	i += COMMENT_LENGTH;
	*(int *)(rez + i) = 0;
	i += sizeof(int);
	j = 0;
	while (j < cont->cmd_count)
	{
		write_cmnd(rez + i, &cont->command_list[j++]);
		i += cont->command_list[j].size;
	}
}

int		asm_translate(t_asmcont *cont, char *file_name)
{
	char	*rez;
	size_t	size;

	if (((size = data_size(cont)) + PROG_NAME_LENGTH + COMMENT_LENGTH + 4 * 4) > MEM_SIZE)
		return (PROGRAM_SIZE_LIMIT);
	if (fuck_connections(cont) < 0)
		return (CONNECTION_ERROR);
	if (rez = ft_strnew(size + PROG_NAME_LENGTH + COMMENT_LENGTH + 4 * 4))
		return (MALLOC_ERROR);
	if (0 > transofrm__data(cont, rez, size))
		return (-1);
}