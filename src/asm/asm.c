/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 15:59:01 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/08/14 22:32:07 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_error()
{
	char	*err[2];

	err[0] = g_error_code ? "COMPILATION ERROR %d\n%s\nLine: %d, %d\n"
	: "COMPILATION ERROR %d\n";
	if (g_error_code == MALLOC_ERROR)
		err[1] = MALLOC_ERROR_STR;
	if (g_error_code == SOURCE_EXTENSION_ERROR)
		err[1] = SOURCE_EXTENSION_ERROR_STR;
	if (g_error_code == OPEN_FILE_ERROR)
		err[1] = OPEN_FILE_ERROR_STR;
	if (g_error_code == LABEL_SIZE_ERROR)
		err[1] = LABEL_SIZE_ERROR_STR;
	if (g_error_code == LABEL_FORBIDDEN_CHAR)
		err[1] = LABEL_FORBIDDEN_CHAR_STR;
	if (g_error_code == COMMAND_NOT_FOUND)
		err[1] = COMMAND_NOT_FOUND_STR;
	if (g_error_code == ARGS_ERROR)
		err[1] = ARGS_ERROR_STR;
	if (g_error_code == PROGRAM_SIZE_LIMIT)
		err[1] = PROGRAM_SIZE_LIMIT_STR;
	if (g_error_code == CONNECTION_ERROR)
		err[1] = CONNECTION_ERROR_STR;
	if (g_error_code == NONE_QUOTE_ERROR)
		err[1] = NONE_QUOTE_ERROR_STR;
	if (NONE_PROG_NAME_ERROR == g_error_code)
		err[1] = NONE_PROG_NAME_STR;
	if (NONE_COMMENT_ERROR == g_error_code)
		err[1] = NONE_COMMENT_STR;
	if (TOO_LONG_NAME_ERROR == g_error_code)
		err[1] = TOO_LONG_NAME_STR;
	if (TOO_LONG_COMMENT_ERROR == g_error_code)
		err[1] = TOO_LONG_COMMENT_STR;
	ft_printf(err[0], g_error_code, err[1], g_row, g_column + 1);
}

char		*what_flag(int *flag, int argc, char **argv)
{
	t_args_rez	*cont;
	char		*rez;
	char		*cpy;

	if (!(cont = new_arguments_cont()))
		return (NULL);
	rez = NULL;
	//add_arg(cont, 1, "-s --stdout --to_console", "");
	add_arg(cont, 1, "-t --strict", "");
	*flag = 0;
	args_anal(argv, argc, cont);
	if (cont->not_expected)
		rez = ft_strdup(cont->not_expected->content);
	if (cont->flags)
		*flag |= cont->flags->hasvalue ? fl_stdout : 0;
	if (cont->flags && cont->flags->next)
		*flag |= cont->flags->next->hasvalue ? fl_strict : 0;
	free_args_rez(&cont);
	cpy = rez;
	rez = ft_strtrim(rez);
	free(cpy);
	return (rez);
}

int		main(int argc, char **argv)
{
	int		*flag_mode;
	char	*cpy;
	char	*path;

	g_error_code = 0;
	g_column = 0;
	g_row = 0;
	path = what_flag((flag_mode = &g_flag), argc, argv);
	if (path)
	{
		if ((g_error_code = cor_open_file(path, *flag_mode)))
			print_error();
		else if (!(*flag_mode & fl_stdout))
		{
			cpy = ft_strreplacelast(path, SOURCE_EXTENSION, ASM_OUT_EXTENSION);
			ft_printf("Writing output program to %s successful\n", cpy 
				? cpy : "!malloc error!");
			if (cpy)
				free(cpy);
		}
		ft_strdel(&path);
	}
	else
		ft_printf("Usage: %2s [-a] <sourcefile.s>\n(-t, -s)\n", argv[0]);
	return (g_error_code ? 1 : 0);
}
