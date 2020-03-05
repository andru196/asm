/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru196 <andru196@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 16:14:38 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/03/06 00:52:53 by andru196         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include <fcntl.h>
# include "op.h"
# include "libft.h"

# define BUF_COR_SIZE 500
# define SIZE_REG 1
/*
** ERRORS
** CODES
*/

# define MALLOC_ERROR			-1
# define SOURCE_EXTENSION_ERROR 100
# define OPEN_FILE_ERROR		22
# define LABEL_SIZE_ERROR		-(T_LAB)
# define LABEL_FORBIDDEN_CHAR	-80
# define COMMAND_NOT_FOUND		-404
# define ARGS_ERROR				-101
# define PROGRAM_SIZE_LIMIT		-800
# define CONNECTION_ERROR		-777

# define MAX_COMMANDS	CHAMP_MAX_SIZE / 2
# define MAX_WORD_LEN	64

typedef struct s_row t_row;
typedef struct s_command t_command;
typedef struct s_label t_label;
typedef struct s_cmnd_label_link t_cmnd_label_link; 
typedef struct s_asmcont t_asmcont;

 struct		s_row 
{
	char			has_label;
	t_command		*cmd;
	char			arg_num;
	
};


struct		s_command
{
	unsigned char		cmnd_num;
	unsigned char		arg_size[MAX_ARGS_NUMBER];
	unsigned char		is_lbl[MAX_ARGS_NUMBER];
	long long			arg[MAX_ARGS_NUMBER];
	int					row;
	unsigned char		size;
};

struct		s_label
{
	char				name[T_LAB + 1];
	t_command			*dst;
	int					row;
	t_label			*next;
};

struct		s_cmnd_label_link
{
	t_label				*label;
	t_command			*command;
	size_t				arg_num;
	t_cmnd_label_link	*next;
};

struct 			s_asmcont
{
	int					row;
	int					col;
	char				*champ_name;
	char				*comment;
	size_t				cmd_count;
	t_command			*command_list;
	t_label				*label_list;
	t_cmnd_label_link	*conn_list;
};

int					check_flags(char **argv, int argc, char *flag);
int					cor_open_file(char *file_name, int flag);
void				print_error(int er_code);
int					init_container(t_asmcont *cont);
t_cmnd_label_link	*new_connect(t_asmcont *cont, int arg_n, char *lbl_name);
t_label				*new_label(t_asmcont *cont, char *str);
int					new_command(t_asmcont *cont, int command);
int					cpy_word(char *dst, char *src);
int					label_check(t_asmcont *c, char *word, int len);
int					command_check(t_asmcont *cont, char *word, char **tr, int len);
void				skip_space(t_asmcont *c, char **str);
int					asm_translate(t_asmcont *cont, char *file_name, int flag);

#endif
