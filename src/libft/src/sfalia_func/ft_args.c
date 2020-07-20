/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanya <tanya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 21:49:25 by andru196          #+#    #+#             */
/*   Updated: 2020/07/20 21:33:49 by tanya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cli_helper.h"

t_arg	*new_arg(char isflag)
{
	t_arg *rez;

	rez = (t_arg *)malloc(sizeof(t_arg));
	if (!rez)
		return (NULL);
	rez->description = NULL;
	rez->names = NULL;
	rez->hasvalue = 0;
	rez->isflag = isflag;
	rez->value = NULL;
	return (rez);
}

/*
** Сформировать контейнер для работы с аргументами
*/

t_args_rez *new_arguments_cont()
{
	t_args_rez *rez;

	rez = (t_args_rez *)malloc(sizeof(t_args_rez));
	if (!rez)
		return (NULL);
	rez->has_args = 0;
	rez->flags = NULL;
	rez->args = NULL;
	return (rez);
}

/*
** Добавить аргумент к ранее сформированному контейнеру
*/

int		add_arg(t_args_rez *args, char isflag, char *names, char *desc)
{
	t_arg	*rez;
	t_arg	*tmp;

	rez = new_arg(isflag);
	if (!rez)
		return (-1);
	rez->description = desc;
	rez->names = names;
	if (isflag)
		tmp = args->flags;
	else
		tmp = args->args;
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
	return (0);
}

t_arg	*find_word(t_args_rez *args, char *word)
{
	t_arg	*tmp;
	char	*point;
	int		len;
	int 	flag;

	len = ft_strlen(word);
	tmp = args->args ? args->args : args->flags;
	flag = args->args ? 0 : 1;
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
	char	**words;
	t_arg	*arg;

	i = 0;
	while (++i < argc)
	{
		if (!(arg = find_word(ret, args[i])))
		{
			ft_lstadd(&ret->not_expected, ft_lstnew(args[i], ft_strlen(args[i])));
			continue;
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

static void del_lst(void *content, size_t content_size)
{
	ft_memdel(&content);
}

void free_args_rez(t_args_rez **args)
{
    t_arg *tmp;

	if (!args || !(*args))
		return ;
    while ((*args)->flags)
    {
        tmp = (*args)->flags->next;
        free((*args)->flags);
        (*args)->flags = tmp;
    }
	while ((*args)->args)
    {
        tmp = (*args)->args->next;
		if ((*args)->args->value)
			free((*args)->args->value);
        free((*args)->args);
        (*args)->args = tmp;
    }
	if ((*args)->not_expected)
		ft_lstdel(&(*args)->not_expected, *del_lst);
	free(*args);
	*args = NULL;
}

/*
int main (int argc, char **argv)
{
	t_args_rez *exampl = new_arguments_cont();
	add_arg(exampl, 0, "-t -type -туйп", "type desc");
	add_arg(exampl, 1, "-typoe_govno", "lox");
	add_arg(exampl, 1, "-govno -ggg", "blya");
	add_arg(exampl, 1, "-bbb", "");
	args_anal(argv, argc, exampl);
	t_arg *tmp;
	tmp = exampl->args;
	printf("args\n");
	while(tmp)
	{
		printf("arg:%s, value:%s\n", tmp->names, tmp->value);
		tmp = tmp->next;
	}
	tmp = exampl->flags;
	printf("flags\n");
	while(tmp)
	{
		printf("flag:%s, hasvalues:%d\n", tmp->names, tmp->hasvalue);
		tmp = tmp->next;
	}
	t_list *temp = exampl->not_expected;
	printf("not_expected\n");
	while(temp)
	{
		printf("conteent:%s\n", temp->content);
		temp = temp->next;
	}
	//printf("%s, %s, %d \n", exampl->not_expected->content, exampl->args->value, exampl->flags->value);
	free_args_rez(&exampl);
}
*/