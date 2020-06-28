# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: andru196 <andru196@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/28 20:41:38 by ycorrupt          #+#    #+#              #
#    Updated: 2020/06/28 14:43:44 by andru196         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	asm
DIR_ASM			=	./src/asm/
SRCS_ASM		=	asm_cor_init.c \
					asm_cpy_word.c \
					asm_translate.c \
					asm.c \
					cor_command_check.c \
					cor_label_check.c \
					init_struct.c \
					read_cor_file.c
SRCS			=	$(addprefix $(DIR_ASM), $(SRCS_ASM)) \
					src/op.c
OBJ				=	$(patsubst %.c, %.o, $(SRCS))
CC				=	clang
FLAGS			=	-Wall -Wextra -Werror -g
LIBRARY			=	src/libft/
LIBFT			=	$(LIBRARY)libft.a
HEADERS			=	includes/ $(LIBRARY)includes
INCLUDES		=	-I includes/ -I $(LIBRARY)includes

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) -L $(LIBRARY) -lft

$(LIBFT):
	make -C $(LIBRARY)

%.o : %.c $(HEADERS)
	$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@

clean:
	rm -f $(OBJ)
	make -C $(LIBRARY) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBRARY) fclean

re: fclean all