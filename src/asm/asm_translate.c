/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_translate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru196 <andru196@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 15:38:53 by andru196          #+#    #+#             */
/*   Updated: 2020/03/04 23:28:05 by andru196         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern t_op op_tab[OP_TAB_SIZE];

size_t	data_size(t_asmcont *c)
{
	size_t		rez;
	size_t		cmd_size;
	size_t		i;
	int			j;

	rez = 0;
	i = -1;
	while (++i < c->cmd_count)
	{
		j = -1;
		cmd_size = 1 + (size_t)op_tab[c->command_list[i].cmnd_num].args_types_code;
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
		rez += cmd_size;
	}
	return (rez);
}

int		fuck_connections(t_asmcont *c)
{
	t_cmnd_label_link	*tmp;
	t_cmnd_label_link	*pre;
	int					i;

	pre = c->conn_list;
	while (pre)
	{
		tmp = pre;
		if (!tmp->label->dst)
			return (-1);
		i = 0;
		while (tmp->label->dst - i  > tmp->command) //Оттестить участок
			tmp->command->arg[tmp->arg_num] += (tmp->command + i++)->size;
		while (tmp->label->dst - i < tmp->command)
			tmp->command->arg[tmp->arg_num] -= (tmp->command + i--)->size;
		free(tmp);
		pre = pre->next;
	}
	return (0);
}

char		type_code(t_command *cmd)
{
	char rez;

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
		rez |= REG_CODE << 2;
	else if (cmd->arg_size[2] == T_IND)
		rez |= IND_CODE << 2;
	else if (cmd->arg_size[2] == T_DIR)
		rez |= DIR_CODE << 2;
	return (rez);
}

void write_n_num(char **dst, long long n, unsigned char bytes)
{
	if (n >= ((long long)1 << bytes * 8))
		n %= 1 << ((long long)bytes * 8 - 1);
	while (bytes)
	{
		**dst = *((char *)&n + (sizeof(long long) - --bytes));
		**dst = ((**dst & 0xf0) >> 4) | ((**dst & 0x0f) << 4); 
		(*dst)++;
	}
}

void	write_cmnd(char *dst, t_command *cmd)
{
	int	i;

	*dst++ = cmd->cmnd_num;
	if (op_tab[cmd->cmnd_num].args_types_code)
		*dst++ = type_code(cmd);
	i = -1;
	while (++i < op_tab[cmd->cmnd_num].args_num)
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
	size_t			i;
	size_t			j;

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
	return (0);
}

int		zapisat(char *rez, char *file_name, int flag, size_t size)
{
	char	*file_name_cor;
	int		name_len;
	int		fd;

	name_len = ft_strlen(file_name);
	file_name_cor = malloc(name_len + 2);
	ft_strcpy(file_name_cor, file_name);
	file_name_cor[name_len- 1] = '\0';
	ft_strcat(file_name_cor, "cor");
	fd = open(file_name_cor, O_WRONLY);
	if (flag == 1)
		write(fd, rez, size);
	else
		write(1, rez, size);
	close(fd);
	return (0);
}

int		asm_translate(t_asmcont *cont, char *file_name, int flag)
{
	char	*rez;
	size_t	size;

	if ((size = data_size(cont) + PROG_NAME_LENGTH + COMMENT_LENGTH + 4 * 4) > MEM_SIZE)
		return (PROGRAM_SIZE_LIMIT);
	if (fuck_connections(cont) < 0)
		return (CONNECTION_ERROR);
	if (!(rez = ft_strnew(size)))
		return (MALLOC_ERROR);
	if (0 > transofrm_data(cont, rez, size))
		return (-1);
	zapisat(rez, file_name, flag, size);
	free(rez);
	return (0);
}