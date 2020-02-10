/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru196 <andru196@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 16:14:38 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/02/10 21:54:35 by andru196         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include <fcntl.h>
# include "op.h"
# include "libft.h"

# define BUF_COR_SIZE 500

/*
** ERRORS
** CODES
*/

# define MALLOC_ERROR			-1
# define SOURCE_EXTENSION_ERROR 100
# define OPEN_FILE_ERROR		22
# define LABEL_SIZE_ERROR		-(T_LAB)
# define LABEL_FORBIDDEN_CHAR	-80

# define MAX_COMMANDS	CHAMP_MAX_SIZE / 2
# define MAX_WORD_LEN	64


typedef struct		s_row 
{
	char			has_label;
	t_command		*cmd;
	char			arg_num;
	
}					t_row;


typedef struct		s_command
{
	unsigned char		cmnd_num;
	unsigned char		arg_size[3];
	long long			arg[3];
	int					row;
}					t_command;

typedef struct		s_label
{
	char				name[T_LAB];
	t_command			*dst;
	int					row;
	t_label			*next;
}					t_label;

typedef struct		s_cmnd_label_link
{
	t_label				*label;
	t_command			*command;
	size_t				arg_num;
	t_cmnd_label_link	*next;
}					t_cmnd_label_link;

typedef struct 			s_asmcont
{
	int					row;
	int					col;
	size_t				cmd_count;
	t_command			*command_list;
	t_label				*label_list;
	t_cmnd_label_link	*conn_list;
}         				 t_asmcont;

int					chaeck_flags(char **argv, int argc, char *flag);
int					cor_open_file(char *file_name, int flag);
void				print_error(int er_code);
int					init_container(t_asmcont *cont);
t_cmnd_label_link	*new_connect(t_asmcont *cont, int arg_n, char *lbl_name);
t_label				*new_label(t_asmcont *cont, char *str);
int					new_command(t_asmcont *cont, int command);
int					cpy_word(char *dst, char *src);
int					label_check(t_asmcont *c, char *word, int len);
int					command_check(t_asmcont *cont, char *word, char *str, int len);

#endif
