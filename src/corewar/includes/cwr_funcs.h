/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwr_funcs.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 21:21:22 by mschimme          #+#    #+#             */
/*   Updated: 2020/08/02 12:08:47 by mschimme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CWR_FUNCS_H
# define CWR_FUNCS_H
# include "cwr.h"


/*
******************		prep_rout (parsing) funcs:		************************
*/

void		ft_read_params(char ***argv, t_world *nexus, int *champ_count);
uint8_t		ft_scan_lines(char ***argv, t_world *nexus, int *champ_count);
uint8_t		ft_parse_fdump(char ***argv, t_world *nexus, int *champ_count);
uint8_t		ft_parse_champ(char ***argv, int *champ_count, int id, \
																t_world *nexus);
int			ft_get_n_flag(char ***argv, t_world *nexus);
int			ft_read_champ_file(char *file, int id, t_champ *this, \
														t_vasa **last_error);
void		ft_init_champ(t_champ *this, int id, t_vasa **champ_error);
uint8_t		*ft_champ_body_alloc(size_t ch_size, t_vasa **champ_err);
void		ft_clear_champ(t_champ *this);
uint8_t		ft_supervise_input(t_world *nexus, int ch_amount);
void		ft_prep_battle(t_world *nexus, int champs);
void		ft_check_id(t_vasa **errors_head, t_champ *champs, int ch_amount);


/*
******************				SERVice funcs:			************************
*/

int			ft_are_digits(const char *str);
int			ft_are_ndigits(const char *start, const char *end);

void		ft_manage_world(t_world *nexus);									//**Завершающая функция. Чистит некторое говно.
void		ft_wipe_champs(t_champ *ptr);
void		ft_del_carry(void *ptr, size_t size);								//? Пока не нужна, используется ft_del
void		ft_del_error(void *ptr, size_t size);								//? Пока не нужна, используется ft_del
int32_t		bytecode_to_int32(const uint8_t *bytecode, size_t size);			//TODO: Удалить после прогона тестами, заменить на _SW_ENDIAN, в случае успеха.
int			ft_prox_err_ret(t_vasa **error_head, void *object, \
															t_err_rout errfunc);
void		ft_prox_err_malloc(const char *var, const char *par_func);
int			ft_cyc_left_grt_right(void *a, void *b);
int			ft_cyc_left_lsr_right(void *a, void *b);




/*
******************				errors funcs:			************************
** Are not supposed to allocate memory for error messages.
*/
void		ft_show_man(void);
void		ft_err_fdump_notnbr(t_vasa **head, void *object);
void		ft_err_fdump_inter(t_vasa **head, void *object);
void		ft_err_fn_notnbr(t_vasa **head, void *object);
void		ft_err_fn_inter(t_vasa **head, void *object);
void		ft_err_not_champ(t_vasa **head, void *object);
void		ft_err_nochamps(t_vasa **head, void *object);
void		ft_err_invalid_filename(t_vasa **head, void *object);
void		ft_err_invalid_parameter(t_vasa **head, void *object);
void		ft_err_champ_limit(t_vasa **head, void *object);
void		ft_err_id_doubled(t_vasa **head, void *object);
void		ft_err_id_behind_fighters(t_vasa **head, void *object);
void		ft_show_compconf(void);

/*
******************		Champion parsing errors funcs:	************************
** Are not supposed to allocate memory for error messages.
*/
int			ft_ch_err_manager(char *filename, t_vasa **subchain_head, \
											t_vasa **chain_head, t_champ *this);
void		ft_err_invalid_cwr_magic(t_vasa **last, void *object);
void		ft_err_invalid_name(t_vasa **last, void *object);
void		ft_err_invalid_filesize(t_vasa **last, void *object);
void		ft_err_invalid_champsize(t_vasa **last, void *object);
void		ft_err_invalid_separator(t_vasa **head, void *object);
void		ft_err_invalid_comment(t_vasa **head, void *object);
void		ft_err_invalid_bodysize(t_vasa **head, void *object);

/*
******************			Built-in test funcs:		************************
*/

int32_t		bytecode_to_int32(const uint8_t *bytecode, size_t size);


#endif