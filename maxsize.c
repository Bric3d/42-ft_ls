/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maxsize.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 16:55:15 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/30 16:57:01 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_usersize(t_list *list)
{
	int	usersize;
	int	i;

	usersize = 0;
	while (list->prv)
		list = list->prv;
	while (list->nxt)
	{
		i = ft_strlen(list->username);
		if (usersize < i)
			usersize = i;
		list = list->nxt;
	}
	i = ft_strlen(list->username);
	if (usersize < i)
		usersize = i;
	return (usersize);
}

int		ft_groupsize(t_list *list)
{
	int	groupsize;
	int	i;

	groupsize = 0;
	while (list->prv)
		list = list->prv;
	while (list->nxt)
	{
		i = ft_strlen(list->groupname);
		if (groupsize < i)
			groupsize = i;
		list = list->nxt;
	}
	i = ft_strlen(list->groupname);
	if (groupsize < i)
		groupsize = i;
	return (groupsize);
}

int		ft_linksize(t_list *list)
{
	int	maxsize;
	int	i;

	maxsize = 0;
	while (list->nxt)
	{
		i = ft_countnum(list->nlink);
		if (maxsize < i)
			maxsize = i;
		list = list->nxt;
	}
	i = ft_countnum(list->nlink);
	if (maxsize < i)
		maxsize = i;
	return (maxsize);
}

t_size	*ft_calcsize(t_list *list, t_arg *arg)
{
	t_size	*size;

	size = NULL;
	if (list && arg->l == 1)
	{
		if (!(size = (struct s_size*)ft_memalloc(sizeof(struct s_size))))
		{
			ft_error(0, "Malloc");
			return (NULL);
		}
		list = ft_maxsize(list, size);
		size->groupsize = ft_groupsize(list);
		size->usersize = ft_usersize(list);
		size->linksize = ft_linksize(list);
	}
	return (size);
}

t_list	*ft_maxsize(t_list *list, t_size *size)
{
	int		maxsize;
	int		i;
	t_list	*first;

	maxsize = 0;
	while (list->prv)
		list = list->prv;
	first = list;
	while (list->nxt)
	{
		size->total = list->st_blocks + size->total;
		i = ft_countnum(list->st_size);
		if (maxsize < i)
			maxsize = i;
		list = list->nxt;
	}
	size->total = list->st_blocks + size->total;
	i = ft_countnum(list->st_size);
	if (maxsize < i)
		maxsize = i;
	size->size = maxsize;
	return (first);
}
