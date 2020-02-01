/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 16:14:38 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/02/01 14:30:01 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include <fcntl.h>
# include "op.h"
# include "libft.h"

# define BUF_COR_SIZE 500

# define SOURCE_EXTENSION_ERROR 100
# define OPEN_FILE_ERROR		22

typedef struct		s_command
{
  unsigned char		cmnd_num;
  unsigned char		arg_size[3];
  long long			arg[3];
  t_command			*next;
}					t_command;

typedef struct		s_label
{
  char				name[T_LAB];
  t_command			*dst;
  t_label			*next;
}					t_label;

typedef struct		s_cmnd_label_link
{
  t_label			*label;
  t_command			*command;
  t_cmnd_label_link	*next;
}					t_cmnd_label_link;


int					chaeck_flags(char **argv, int argc, char *flag);
int					cor_open_file(char *file_name, int flag);
void				print_error(int er_code);

#endif
