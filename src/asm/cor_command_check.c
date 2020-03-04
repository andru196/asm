/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cor_command_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru196 <andru196@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 21:47:10 by andru196          #+#    #+#             */
/*   Updated: 2020/03/04 21:37:33 by andru196         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern t_op op_tab[OP_TAB_SIZE];

int	digits_count(char *str)
{
	int i;

	i = 0;
	while (ft_isdigit(*str++))
		i++;
	return (i);	
}

int	arg_label_check(char *wrd)
{
	int i;

	i = 0;
	while (*wrd && *wrd != SEPARATOR_CHAR)
	{
		if (!ft_charinstr(LABEL_CHARS, *wrd++))
			return (0);
		i++;
	}
	return (i && i <= T_LAB);
}

 t_cmnd_label_link	*add_label_arg(t_asmcont *c, char *wrd, int arg_n)
 {
	int					i;
	char				wrd_cpy[T_LAB + 1];
	t_cmnd_label_link	*rez;

	ft_bzero(wrd_cpy, T_LAB + 1);
	i = 0;
	while (*wrd && *wrd != SEPARATOR_CHAR)
		wrd_cpy[i++] = *wrd++;
	rez = c->conn_list;
	if (!rez)
		return (c->conn_list = new_connect(c, arg_n, wrd_cpy));
	else
		while (rez->next)
			rez = rez->next;
	return (rez->next = new_connect(c, arg_n, wrd_cpy));
 }

int	args_check(t_asmcont *cont, int com_pos, int arg_num, char *word)
{
	long long	rez;
	const char	sep[2] = {SEPARATOR_CHAR, '\0'};
	
	rez = 0;
	if (arg_num + 1 < op_tab[cont->command_list[com_pos].cmnd_num].args_num
		&& word[ft_strlen(word) - 1] != SEPARATOR_CHAR)
		return (-1);
	if (ft_strendwith(word, (char *)sep))
		word[ft_strlen(word) - 1] = '\0';
	if (*word == 'r')
	{
		if ((rez = ft_atoi(++word)) > REG_NUMBER || rez < 1
			|| (word[digits_count(word)] != SEPARATOR_CHAR && word[digits_count(word)] != '\0'))
			return (-1);
		if (!(op_tab[cont->command_list[com_pos].cmnd_num].args_types[arg_num] & T_REG))
			return (-1); //соответствие типа
		cont->command_list[com_pos].arg_size[arg_num] = T_REG;
		cont->command_list[com_pos].arg[arg_num] = rez;
	}
	else if (*word == DIRECT_CHAR)
	{
		if (!(op_tab[cont->command_list[com_pos].cmnd_num].args_types[arg_num] & T_DIR))
			return (-1); //соответствие типа
		if (*(word + 1) == LABEL_CHAR)
		{
			if (!arg_label_check(word + 2))
				return (-1);
			add_label_arg(cont, word + 2, arg_num);
			//Тут ещё вариант если добавят что-то тип :huy + 228
			cont->command_list[com_pos].is_lbl[arg_num] = 1;
		}
		else
		{
			rez = ft_atoi(word + 1);
			if (!str_num_eq(rez, word + 1))
				return (-1);
		}
		cont->command_list[com_pos].arg[arg_num] = rez;
		cont->command_list[com_pos].arg_size[arg_num] = T_DIR;
		
	}
	else //T_IND
	{
		if (!(op_tab[cont->command_list[com_pos].cmnd_num].args_types[arg_num] & T_IND))
			return (-1); //соответствие типа
		if (*(word + 1) == LABEL_CHAR)
		{
			if (!arg_label_check(word + 1))
				return (-1);
			add_label_arg(cont, word + 2, arg_num);
			cont->command_list[com_pos].is_lbl[arg_num] = 1;
		}
		else
		{
			rez = ft_atoi(word + 1);
			if (!str_num_eq(rez, word))
				return (-1);
		}
		cont->command_list[com_pos].arg[arg_num] = rez;
		cont->command_list[com_pos].arg_size[arg_num] = T_IND;
	}
	return (0);
}

int	command_check(t_asmcont *cont, char *word, char **str, int len)
{
	int		i;
	int		new_c;
	int		j;

	i = 0;
	while (ft_strcmp(op_tab[i].name, word) && i < OP_TAB_SIZE)
		i++;
	if (i == OP_TAB_SIZE)
		return (COMMAND_NOT_FOUND);
	cont->col += len;
	new_c = new_command(cont, i);
	j = 0;
	ft_bzero(word, ft_strlen(word));
	while (j < op_tab[i].args_num)
	{
		skip_space(cont, str);
		*str += cpy_word(word, *str) + ft_strendwith(word, ",");
		if (args_check(cont, new_c, j++, word) == -1)
			return (ARGS_ERROR);
	}
	return (1);
}
