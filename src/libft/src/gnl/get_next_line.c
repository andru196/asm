/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 14:08:08 by mschimme          #+#    #+#             */
/*   Updated: 2021/04/10 20:55:04 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef const void	t_cv;

#define sizeof sizeof

int					g_gnl_read;

/*
** ft_lstmk doest 3 things (according to it's flag _fl_).
** For flag > 1 it creates new empy list (with no fluff).
** If flag == 2 it creates LST with content of size INT to write in a FD num.
** If flag == 3 it creates LST with content of size BUFF_SIZE + 1 for BuffList.
** Successfull creation of LST returns 0.
** If list creation is failed or memory allocation for content is failed,
** It's considered as critical error, function frees any of memory allocated.
** Flag == 0 means it's time to destroy fd-lists constraction.
*/

static int	ft_lstmk(int fl, t_list **lst, int val, t_list **fd_lst)
{
	if (fl > 1)
	{
		if (!as((void **)lst, ft_lstnew(NULL, 0)))
		{
			ft_lstdel(fd_lst, &ft_del);
			return (-1);
		}
		if ((fl == 2) && !as(&(*lst)->content, ft_memalloc(sizeof(int))))
		{
			ft_lstdel(fd_lst, &ft_del);
			*lst = NULL;
			return (-1);
		}
		if ((fl == 3) && !as(&(*lst)->content, ft_memalloc(BUFF_SIZE + 1)))
		{
			ft_lstdel(fd_lst, &ft_del);
			*lst = NULL;
			return (-1);
		}
		(*lst)->content_size = sizeof(int);
		(*(int *)((*lst)->content)) = val;
		return (0);
	}
	ft_lstdel(lst, &ft_del);
	return (-1);
}

/*
** ft_fdr does 3 things:
** Creates fd_lsts if no list of a given fd is found.
** Links them together (in the way, opposite to ft_lstadd), new list is being
** added to the end of the chain.
** Picks up propper list, scanning first 4 bytes of lst->content.
*/

static t_list	*ft_fdr(t_list **fd_lst, int fd, t_list *last, \
								t_list *pr)
{
	if (fd == -1)
		return (NULL);
	if (!(*fd_lst))
	{
		if (ft_lstmk(2, fd_lst, fd, fd_lst) == -1)
			return (NULL);
		return (*fd_lst);
	}
	else
	{
		while (last)
		{
			if (*(int *)(last->content) == fd)
				return (last);
			if (last->next == NULL)
				pr = last;
			last = last->next;
		}
		if (ft_lstmk(2, &(pr->next), fd, fd_lst) == -1)
			return (NULL);
		return (pr->next);
	}
}

/*
** ft_rs (ft_remain scanner) does few things.
** It searches '\n' or '\0' in given fd_list.
** If both of them are found, it choses the closest to beginning of the string.
** It creates substring for *line, modding fd_list->content and ->content_size.
** bgy[0] - pointer to slide along the fd_list->content. It tries to point at
** '\n' or '\0' in it.
** bgy[1] - pointer to a new version of fd_list->content, created after
** *line substring is substracted.
** bgy[2] - pointer to search for '\0'. Sole purpose pointer to give its value
** to bgy[0] if a '\0' closer to fd_list->content is found.
** Function returns 0 if something found in fd_lst->content is found.
** Otherwise it returns 2. Why not?!
*/

static int	ft_rs(char **line, t_list *rem, t_list **fd_lst)
{
	void			*bgy[3];
	const int		si = sizeof(int);

	bgy[0] = ft_memchr(rem->content + sizeof(int), '\n',
			rem->content_size - sizeof(int));
	if ((bgy[0]) && as(&bgy[0], bgy[0] + 1))
	{
		if (!as((void **)line, ft_memalloc(bgy[0] - rem->content - si)))
			return (ft_lstmk(2, fd_lst, 0, fd_lst));
		ft_memcpy((void *)(*line), rem->content + si, bgy[0] - \
									rem->content - 1 - si);
		if (!*(char *)(bgy[0] - 1) && (bgy[0] - 1) != rem->content + si)
			bgy[0] -= 1;
		g_gnl_read = (int)(bgy[0] - rem->content - si - 1);
		rem->content_size -= (bgy[0] - rem->content - si);
		if (!as(&bgy[1], ft_memalloc(rem->content_size)))
			return (ft_lstmk(2, fd_lst, 0, fd_lst));
		ft_memcpy(bgy[1] + si, bgy[0], rem->content_size - si);
		*(int *)bgy[1] = *(int *)rem->content;
		free(rem->content);
		rem->content = bgy[1];
		return (0);
	}
	return (2);
}

/*
** ft_rs processes cases when either are yet in search of '\0' or '\n' or
** ened up to come to an end of file without finding these symbols.
** In first case functiong concatenates apropriate fd_list->content (ar[0])
** with BUFF->content (ar[1]).
** In second case it transferes rem to *line, preparing fd_list for next use
** or destroing whole chain (depends on status of other elements of chain).
*/

/*
**	replaced by ft_replace_cnt:
**		free(ar[0]->content);
**		ar[0]->content = (void *)ar[2];
**		ar[0]->content_size += ar[1]->content_size;
**		ft_lstdelone(&ar[1], &ft_del);
*/

static int	ft_hopper(t_lst **ar, t_list **fdl, char **lin, size_t fl)
{
	const int		si = sizeof(int);

	if (fl == 1)
	{
		if (!as((void **)&ar[2], ft_memalloc(ar[0]->cs + ar[1]->cs)))
			return (ft_lstmk(2, fdl, 0, fdl));
		ft_memcpy(ft_memcpy(ar[2], ar[0]->cnt, ar[0]->cs) + \
			ar[0]->cs, ar[1]->cnt, ar[1]->cs);
		ft_replace_cnt((t_list *)ar[0], (t_list **)&ar[1], (void *)ar[2]);
		return (get_next_line(*(const int *)(ar[0]->cnt), lin));
	}
	if (!as((void **)lin, ft_memalloc(ar[0]->cs - si + 1)))
		return (ft_lstmk(2, fdl, 0, fdl));
	ft_memcpy((*lin), ar[0]->cnt + si, ar[0]->cs - si);
	ft_bzero(ar[0]->cnt + si, ar[0]->cs - si);
	g_gnl_read = (int)ar[0]->cs - (int)si;
	ar[0]->cs = si;
	ar[2] = (t_lst *)*fdl;
	fl += ar[2]->cs - si;
	while (as((void **)&ar[2], ar[2]->nxt))
		fl += ar[2]->cs - si;
	if (fl == 0)
		ft_lstdel(fdl, &ft_del);
	ft_lstdelone((t_list **)&ar[1], &ft_del);
	return (1);
}

/*
** Nexus function. Gets proper fd_lst, evalueates result of remain scanner.
** Creates buffer (if required).
** Destrois list chain (like in Hopper) when needed.
** pl[0] - for proper fd_list.
** pl[1] - for buffer list.
** pl[2] - points at fdl when need to evaluate chain of lits state.
** ss[0] - holds return of remain scanner.
** ss[1] - is used to calculate chain of lists state. If it's evaluated to
** == 0, that means we're processing last of file descriptors given, thus
** chain of lists is ought to be destroyed (freed). Otherwise there are
** file descriptors that've not reached the end of file.
*/

int	get_next_line(const int fd, char **line)
{
	static t_list	*fdl;
	t_list			*pl[3];
	int				ss[2];

	if (!(as((void **)&pl[0], ft_fdr(&fdl, fd, fdl, fdl)) && !(BUFF_SIZE < 1) && \
			(asi(&ss[0], ft_rs(line, pl[0], &fdl)) != -1)))
		return (-1);
	if (ss[0] == 0)
		return (1);
	if (as((void **)&pl[2], fdl) && (ft_lstmk(3, &pl[1], 0, &fdl) == -1))
		return (-1);
	if (asi(&ss[1], read(fd, pl[1]->content, BUFF_SIZE)) == -1)
		return (ft_wipegnl(&fdl, pl[0], pl[1], pl[2]));
	if (ast(&pl[1]->content_size, (size_t)ss[1]) != 0)
		return (ft_hopper((t_lst **)pl, &fdl, line, 1));
	if (pl[0]->content_size - sizeof(int) == 0 && !as((void **)line, NULL))
	{
		pl[1]->content_size += pl[2]->content_size - sizeof(int);
		while (as((void **)&pl[2], pl[2]->next))
			pl[1]->content_size += pl[2]->content_size - sizeof(int);
		if (pl[1]->content_size == 0)
			ft_lstdel(&fdl, &ft_del);
		return (ft_lstmk(0, &pl[1], 0, NULL) + 1);
	}
	return (ft_hopper((t_lst **)pl, &fdl, line, 0));
}
