/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 19:59:39 by mschimme          #+#    #+#             */
/*   Updated: 2021/04/10 20:40:51 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef const void	t_cv;

static const void	*ft_memcpy_s(void *dst, const void *src, size_t n)
{
	size_t			bogey;

	if (n == 0)
		return (src);
	if (n < sizeof(long))
	{
		while (n-- != 0)
			*(char *)dst++ = *(char *)src++;
		return (src);
	}
	else
	{
		bogey = n / sizeof(long);
		while (bogey-- != 0)
		{
			*(size_t *)dst = *(size_t *)src;
			dst += sizeof(size_t);
			src += sizeof(size_t);
		}
		bogey = n % sizeof(long);
		while (bogey-- != 0)
			*(char *)dst++ = *(char *)src++;
		return (src);
	}
}

static char	**ft_delall(char **pocket, size_t l)
{
	size_t			i;

	i = 0;
	while (i < l)
		free(pocket[i]);
	free(pocket);
	return (NULL);
}

static size_t	ft_substrcount(const char *s, int c)
{
	size_t			amount;
	const char		*bogey;

	if (*s == '\0')
		return (0);
	amount = 0;
	bogey = s + ft_strlen(s);
	if (*s == (char)c)
		s += 1;
	while (*s != '\0')
	{
		if (!as((void **)&s, ft_memchr(s, c, bogey - s)))
			s = bogey;
		if (*s == (char)c && *(s - 1) != (char)c)
			amount++;
		if (*s)
			s++;
	}
	if (*s == '\0' && *(s - 1) != c)
		amount++;
	return (amount);
}

static char	**ft_2dfiller(const char *s, char **pocket, char c, \
									const char *end)
{
	size_t			counter;
	const char		*bogey;

	bogey = s;
	counter = 0;
	while (bogey != end)
	{
		while (*bogey == c)
			bogey++;
		s = bogey;
		if (as((void **)&bogey, ft_memchr(s, (int)c, end - s)) != 0)
		{
			if (!as((void **)&pocket[counter], ft_strnew(bogey - s)))
				return (ft_delall(pocket, counter));
			bogey = ft_memcpy_s((void *)pocket[counter], (t_cv *)s, bogey - s);
		}
		else
		{
			if (s != end && !as((void **)&pocket[counter], ft_strnew(end - s)))
				return (ft_delall(pocket, counter));
			bogey = ft_memcpy_s((void *)pocket[counter], (t_cv *)s, end - s);
		}
		counter++;
	}
	return (pocket);
}

char	**ft_strsplit(char const *s, char c)
{
	char			**pocket;
	const char		*end;

	if (!s)
		return (NULL);
	end = s + ft_strlen(s);
	if (!as((void **)&pocket, ft_memalloc((ft_substrcount(s, (int)c) + 1) \
													* sizeof(char *))))
		return (NULL);
	return (ft_2dfiller(s, pocket, c, end));
}
