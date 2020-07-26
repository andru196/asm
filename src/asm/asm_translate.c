/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_translate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 15:38:53 by andru196          #+#    #+#             */
/*   Updated: 2020/07/26 23:37:22 by sfalia-f         ###   ########.fr       */
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
				cmd_size += SIZE_REG;
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

long long rev_bytes_ll(long long n)
{
	return (((n & 0xff00000000000000) >> (7 * 8))
			| ((n & 0x00ff000000000000) >> (5 * 8))
			| ((n & 0x0000ff0000000000) >> (3 * 8))
			| ((n & 0x000000ff00000000) >> (1 * 8))
			| ((n & 0x00000000ff000000) << (1 * 8))
			| ((n & 0x0000000000ff0000) << (3 * 8))
			| ((n & 0x000000000000ff00) << (5 * 8))
			| ((n & 0x00000000000000ff) << (7 * 8)));
}

int rev_bytes(int n)
{
	return (((n & 0xff000000) >> (3 * 8))
			| ((n & 0x00ff0000) >> (1 * 8))
			| ((n & 0x0000ff00) << (1 * 8))
			| ((n & 0x000000ff) << (3 * 8)));
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
		g_row = tmp->command->row;
		if (!tmp->label->dst)
			return (-1);
		i = 0;
		while (tmp->label->dst - i  > tmp->command)
			tmp->command->arg[tmp->arg_num] += (tmp->command + i++)->size;
		while (tmp->label->dst - i < tmp->command)
			tmp->command->arg[tmp->arg_num] -= (tmp->command + --i)->size;
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
	int i;

	if (n >= ((long long)1 << bytes * 8))
		n %= 1 << ((long long)bytes * 8 - 1);
	i = 0;
	//if (n < 0)
	//{
		n = rev_bytes_ll(n);
		i = sizeof(long long) - bytes;
		bytes = sizeof(long long);
	//}
	while (bytes > i)
	{
		**dst = *(((char *)&n) + i++);
		(*dst)++;
	}
}

int	write_cmnd(char *dst, t_command *cmd)
{
	int		i;
	char	*cpy;

	cpy = dst;
	*dst++ = cmd->cmnd_num + 1;
	if (op_tab[cmd->cmnd_num].args_types_code)
		*dst++ = type_code(cmd);
	i = -1;
	while (++i < op_tab[cmd->cmnd_num].args_num)
	{
		if (cmd->arg_size[i] == T_REG)
			write_n_num(&dst, cmd->arg[i], SIZE_REG);
		else if (cmd->arg_size[i] == T_IND)
			write_n_num(&dst, cmd->arg[i], IND_SIZE);
		else if (cmd->arg_size[i] == T_DIR)
			write_n_num(&dst, cmd->arg[i], DIR_SIZE / (1 + op_tab[cmd->cmnd_num].t_dir_size));
	}
	return (dst - cpy);
}

int		transofrm_data(t_asmcont *cont, char *rez, unsigned size)
{
	size_t			i;
	size_t			j;
	write_n_num(&rez,  COREWAR_EXEC_MAGIC, sizeof(int));
	rez -= sizeof(int);
	i = 0 + sizeof(int);
	ft_strncpy(rez + i, cont->champ_name, PROG_NAME_LENGTH);
	i += PROG_NAME_LENGTH;
	*(int *)(rez + i) = 0;
	i += sizeof(int);
	rez += i;
	write_n_num(&rez,  size - PROG_NAME_LENGTH - COMMENT_LENGTH - 16, sizeof(int));
	rez -= sizeof(int) + i;
	i += sizeof(unsigned);
	ft_strncpy(rez + i, cont->comment, COMMENT_LENGTH);
	i += COMMENT_LENGTH;
	*(int *)(rez + i) = 0;
	i += sizeof(int);
	j = 0;
	while (j < cont->cmd_count)
		i += write_cmnd(rez + i, &cont->command_list[j++]);
	return (0);
}

int		zapisat(char *rez, char *file_name, int flag, size_t size)
{
	char	*file_name_cor;
	int		fd;

	file_name_cor = ft_strreplacelast(file_name, SOURCE_EXTENSION, ASM_OUT_EXTENSION);
	fd = open(file_name_cor, O_WRONLY | O_CREAT, 666);
	free(file_name_cor);
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