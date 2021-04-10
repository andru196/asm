/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 18:53:40 by mschimme          #+#    #+#             */
/*   Updated: 2021/04/10 20:33:06 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*pocket;
	char	*bogey;

	if (!s || !f)
		return (NULL);
	if (!as((void **)&pocket, ft_strnew(ft_strlen(s))))
		return (NULL);
	bogey = pocket;
	while (*s != '\0')
		*bogey++ = f(*s++);
	return (pocket);
}
