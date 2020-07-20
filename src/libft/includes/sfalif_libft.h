/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sfalif_libft.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru196 <andru196@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 13:09:54 by ycorrupt          #+#    #+#             */
/*   Updated: 2020/07/20 22:46:41 by andru196         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_SFALIA_H
# define LIBFT_SFALIA_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>

# define SIZE(type, n) sizeof(type) * (n)

typedef struct	s_array
{
	void	**ptr;
	size_t	len;
	size_t	max;
}				t_array;

int				ft_isspace(int c);
long long int	ft_atoix(char *str);
int				ft_isdigit(int c);
int				ft_charinstr(const char *str, char c);
int				ft_strendwith(char *str, char *end);
int				str_num_eq(long num, char *str);
int				ft_mod(long int num);
char		    *ft_strreplace(char const *str, char *orig, char *sub);
char		    *ft_strreplacefirst(char const *str, char *orig, char *sub);
char		    *ft_strreplacelast(char const *str, char *orig, char *sub);

#endif