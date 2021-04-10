/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 21:49:25 by andru196          #+#    #+#             */
/*   Updated: 2021/04/10 20:40:02 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cli_helper.h"

t_arg	*new_arg(char isflag)
{
	t_arg	*rez;

	rez = (t_arg *)malloc(sizeof(t_arg));
	if (!rez)
		return (NULL);
	rez->description = NULL;
	rez->names = NULL;
	rez->hasvalue = 0;
	rez->isflag = isflag;
	rez->value = NULL;
	rez->next = NULL;
	return (rez);
}

/*
** Сформировать контейнер для работы с аргументами
*/

t_args_rez	*new_arguments_cont(void)
{
	t_args_rez	*rez;

	rez = (t_args_rez *)malloc(sizeof(t_args_rez));
	if (!rez)
		return (NULL);
	rez->has_args = 0;
	rez->flags = NULL;
	rez->args = NULL;
	rez->not_expected = NULL;
	return (rez);
}

/*
** Добавить аргумент к ранее сформированному контейнеру
*/

t_arg	*add_arg(t_args_rez *args, char isflag, char *names, char *desc)
{
	t_arg	*rez;
	t_arg	*tmp;

	rez = new_arg(isflag);
	if (!rez)
		return (rez);
	rez->description = desc;
	rez->names = names;
	tmp = args->args;
	if (isflag)
		tmp = args->flags;
	if (!tmp && isflag)
		args->flags = rez;
	else if (!tmp)
		args->args = rez;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = rez;
	}
	return (rez);
}

t_arg	*find_word(t_args_rez *args, char *word)
{
	t_arg	*tmp;
	char	*point;
	int		len;
	int		flag;

	len = ft_strlen(word);
	tmp = tv(args->args && 1, args->args, args->flags);
	flag = ti(args->args && 1, 0, 1);
	while (tmp)
	{
		point = NULL;
		point = ft_strstr(tmp->names, word);
		if (point && (*(point + len) == '\0' || *(point + len) == ' '))
			return (tmp);
		tmp = tmp->next;
		if (!tmp && !flag)
		{
			tmp = args->flags;
			flag = 1;
		}
	}
	return (NULL);
}

/*
** Провести анализ поданных в программу аргументов
*/

void	args_anal(char **args, int argc, t_args_rez *ret)
{
	int		i;
	t_arg	*arg;

	i = 0;
	arg = NULL;
	while (++i < argc)
	{
		if (!as((void **)arg, find_word(ret, args[i])))
		{
			ft_lstadd(&ret->not_expected, ft_lstnew(args[i],
					ft_strlen(args[i]) + 1));
			continue ;
		}
		if (arg->isflag)
			arg->hasvalue = 1;
		else if (++i < argc)
		{
			if (arg->value)
				free(arg->value);
			arg->value = ft_strdup(args[i]);
			arg->hasvalue = 1;
		}
	}
}
