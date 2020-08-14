/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwr_defs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 21:26:17 by mschimme          #+#    #+#             */
/*   Updated: 2020/08/03 23:56:58 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CWR_DEFS_H
# define CWR_DEFS_H
# include "cwr.h"
# include "op.h"
# include "little_endian.h"

#define _INT_OVF(x) (int)(x) != x
#define _VALID_EXTENSION_ ".cor"
#define DESC_BLOCK PROG_NAME_LENGTH + COMMENT_LENGTH

#if REG_SIZE < 5
#define RTP uint32_t
#else
#define RTP uint64_t
#endif

#define _SEP_TYPE RTP

typedef struct s_world		t_world;
typedef struct s_champ		t_champ;
typedef struct s_carry		t_carry;
typedef struct s_cycle		t_cycle;
typedef struct s_error		t_error;
typedef struct s_vasa		t_vasa;

typedef void	t_err_rout(t_vasa **head, void *object);



# ifndef VASA_H
# define VASA_H
union				u_generic
{
	void			*content;
	t_carry			*carry;
	t_error			*error;
	size_t			cyc_sol;													// Дженерик сам по себе является хранилищем данных типа size_t (хранит номер выгружаемого цикла.)
	size_t			*cyc_arr;													// Дженерик выступает в роли указателя на массив 
};
#endif

typedef struct		s_vasa
{
	union u_generic	gen;
	size_t			content_size;
	struct s_vasa	*next;
}					t_vasa;

struct						s_error
{
	char *argv_tar;																// Указывает на объект ARGV, который оказался ошибочным.
	char *errmessage;															// Тело мессаги, которую надлежит вывести при отработке ошибок.
};

struct						s_cycle
{
	size_t					cycle;												// Текущий цикл. Для производительности есть смысл его убрать в функцию переменной.
	size_t					cyc_to_die;											// Cycles to die (относится к жизням кареток)
	size_t					aftercheck;											// Потому что я тупой (нахера я этот элемент ввел?)
	size_t					checks_sum;											// Тудаже, сука... Чем бля я думал, когда код писал??
	t_vasa					*cyc_to_dunp;										// Относится к флагу -dump. для (while (1) для работы виртуалки, внутри проверка if (cycle XOR cyc_to_dump);
};

struct						s_carry												//! UNDER CONSTRUCTION!
{
	int						id;													// Задается при инциализации каретки.
	uint8_t					op;													// ОПКОД операции, на которую смотрит каретка в данный момент (запись этого барахла - дважды - сразу после отработки предыдущей, а также прямо перед отработкой.)
};

struct						s_champ												// Чемпион, nuff said.
{
	int32_t					id;
	RTP						size;												// Номинальный размер чемпиона (подлежит проверке по факту).
	char					*name;
	char					*desc;
	uint8_t					*body;												// Указатель на код (тело) чемпиона.
};

/*
**	uint8_t	flags:
**	Description of each bit goes in descending: from the highest to lowest.
**	1:						0:
**	1:						0:
**	1:						0:
**	1:						0:
**	1:						0:
**	1:						0:
**	1:						0:
**	1:	Dump arena.			0:	Announce Battle victor.
*/

struct						s_world
{
	char					*progname;
	uint8_t					flags;												// Пока рудимент, что-то пихать сюда смысла нет.
	t_champ					champ[MAX_PLAYERS];
	uint8_t					arena[MEM_SIZE];
	t_champ					*survivor;											// Последний заявивший о своей жизни.
	t_vasa					*carry;												// Указатель на carry, которую надлежит проверять на исполнение.
	t_vasa					*errors;											// Цепочка ошибок, обнаруженных при парсинге строки. 
	t_cycle					cyc;
};

typedef enum
{
	false,
	true
}	t_bool;

#endif