/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 18:52:10 by mschimme          #+#    #+#             */
/*   Updated: 2021/04/10 20:33:16 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	bogey;
	char	*pocket;

	if (!s || !f)
		return (NULL);
	bogey = 0;
	if (!as((void **)&pocket, ft_strnew(ft_strlen(s))))
		return (NULL);
	while (s[bogey] != '\0')
	{
		pocket[bogey] = f(bogey, s[bogey]);
		bogey++;
	}
	return (pocket);
}
