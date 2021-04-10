/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 22:52:48 by sfalia-f          #+#    #+#             */
/*   Updated: 2021/04/10 20:38:43 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline void	whilewhilewhilie(char const *str, char *rez[3], char *orig,
						int len[2])
{
	rez[2] = ft_strstr(str, orig);
	if (rez[2])
		ft_strncpy(rez[0], str, rez[2] - str);
	else
		ft_strcat(rez[0], str);
	rez[0] += ti(rez[2] && 1, (rez[2] - str) + len[1], 0);
}

char	*ft_strreplace(char const *str, char *orig, char *sub)
{
	char	*rez[3];
	int		len[2];

	if (!str || !orig || !sub)
		return (NULL);
	rez[0] = (char *)str;
	len[1] = ft_strlen(sub);
	rez[2] = 0;
	if (!asi(len, ft_strlen(orig)))
		return (ft_strdup(str));
	while (as((void **)rez[0], ft_strstr(rez[0], orig)))
		if (++rez[2])
			rez[0] += len[0];
	if (!as((void **)rez[0], ft_strnew(ft_strlen(str) + (len[1] - len[0]) \
			* (int)rez[2])))
		return (NULL);
	rez[1] = rez[0];
	while (*str)
	{
		whilewhilewhilie(str, rez, orig, len);
		if (rez[2])
			ft_strcat(rez[0] - len[1], sub);
		str += ti(rez[2] && 1, rez[2] - str + len[0], ft_strlen(str));
	}
	return (rez[1]);
}

char	*ft_strreplacefirst(char const *str, char *orig, char *sub)
{
	char	*rez[3];
	int		len[2];

	if (!str || !orig || !sub)
		return (NULL);
	rez[0] = (char *)str;
	len[0] = ft_strlen(orig);
	len[1] = ft_strlen(sub);
	if (!len[0] || !as((void **)&rez[2], ft_strstr(str, orig)))
		return (ft_strdup(str));
	rez[0] = ft_strnew(ft_strlen(str) + (len[1] - len[0]));
	rez[1] = rez[0];
	ft_strncpy(rez[0], str, rez[2] - str);
	rez[0] += rez[2] - str;
	ft_strcat(rez[0], sub);
	ft_strcat(rez[0] + len[1], rez[2] + len[0]);
	return (rez[1]);
}

char	*ft_strreplacelast(char const *str, char *orig, char *sub)
{
	char	*rez[3];
	int		len[2];

	if (!str || !orig || !sub)
		return (NULL);
	rez[0] = (char *)str;
	len[0] = ft_strlen(orig);
	len[1] = ft_strlen(sub);
	if (!len[0] || !as((void **)&rez[2], ft_strstr(str, orig)))
		return (ft_strdup(str));
	rez[0] = ft_strnew(ft_strlen(str) + (len[1] - len[0]));
	rez[1] = rez[2];
	while (as((void **)&rez[2], ft_strstr(rez[2], orig)))
		rez[1] = rez[2]++;
	rez[2] = rez[1];
	rez[1] = rez[0];
	ft_strncpy(rez[0], str, rez[2] - str);
	rez[0] += rez[2] - str;
	ft_strcat(rez[0], sub);
	ft_strcat(rez[0] + len[1], rez[2] + len[0]);
	return (rez[1]);
}
