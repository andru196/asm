/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 18:00:43 by mschimme          #+#    #+#             */
/*   Updated: 2021/04/10 20:32:15 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** We use NULL, thus we need libft.h in order to include stdlib.h
** 	What the hex going on!? First we count length with ft_strlen, adding +1 to
** include \0, then we do memcpy and return it with casting into char *.
*/

char	*ft_strdup(const char *s1)
{
	char	*sub_res;

	if (!as((void **)&sub_res, malloc(sizeof(char) * (ft_strlen(s1) + 1))))
		return (NULL);
	return (ft_strcpy(sub_res, s1));
}
