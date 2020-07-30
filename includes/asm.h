/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 16:14:38 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/07/26 22:57:56 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include <fcntl.h>
# include "op.h"

//# include "deblib.h"
//# include  "ft_printfdefines.h"
//# include  "ft_printf.h"
# include "sfalif_libft.h"
# include "libft.h"

# include "corewar_error.h"

# define BUF_COR_SIZE 500
# define SIZE_REG 1

# define MAX_COMMANDS	CHAMP_MAX_SIZE / 2
# define MAX_WORD_LEN	64

#define QUOTE_CHAR				'"'

typedef struct s_row				t_row;
typedef struct s_command			t_command;
typedef struct s_label				t_label;
typedef struct s_cmnd_label_link	t_cmnd_label_link;
typedef struct s_asmcont			t_asmcont;

struct					s_row
{
	char			has_label;
	t_command		*cmd;
	char			arg_num;
};

struct					s_command
{
	unsigned char		cmnd_num;
	unsigned char		arg_size[MAX_ARGS_NUMBER];
	unsigned char		is_lbl[MAX_ARGS_NUMBER];
	long long			arg[MAX_ARGS_NUMBER];
	int					row;
	unsigned char		size;
};

struct					s_label
{
	char				name[MAX_WORD_LEN + 1];
	t_command			*dst;
	int					row;
	t_label				*next;
};

struct					s_cmnd_label_link
{
	t_label				*label;
	t_command			*command;
	size_t				arg_num;
	t_cmnd_label_link	*next;
};

struct					s_asmcont
{
	char				*champ_name;
	char				*comment;
	size_t				cmd_count;
	t_command			*command_list;
	t_label				*label_list;
	t_cmnd_label_link	*conn_list;
};

int					g_error_code;
int					g_column;
int					g_row;

int					check_flags(char **argv, int argc, char *flag);
int					cor_open_file(char *file_name, int flag);
void				asm_print_error();
int					init_container(t_asmcont *cont);
t_cmnd_label_link	*new_connect(t_asmcont *cont, int arg_n, char *lbl_name);
t_label				*new_label(t_asmcont *cont, char *str);
int					new_command(t_asmcont *cont, int command);
int					cpy_word(char *dst, char *src);
int					cpy_arg_word(char *dst, char *src);
int					label_check(t_asmcont *c, char *word, int len);
int					command_check(t_asmcont *cont, char *word, char **tr, int len);
void				skip_space(char **str);
int					asm_translate(t_asmcont *cont, char *file_name, int flag);
void				prepare_arg(char *word, long long *arg);
void				ast_strrtrim(char *word);

#endif
