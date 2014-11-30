/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 16:47:07 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/30 16:48:43 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_freelist(t_list *list)
{
	list->prv = NULL;
	list->nxt = NULL;
	free(list->name);
	free(list->path);
	free(list->groupname);
	free(list->username);
	list->st_blocks = 0;
	list->st_size = 0;
	list->st_mode = 0;
	list->date = 0;
	list->nlink = 0;
	list->sub = 0;
	free(list);
}

t_list	*ft_freerev(t_list *list)
{
	t_list	*listtmp;

	listtmp = NULL;
	if (list)
	{
		if (list->prv)
			listtmp = list->prv;
		else
			listtmp = NULL;
		ft_freelist(list);
	}
	return (listtmp);
}

t_list	*ft_free(t_list *list)
{
	t_list	*listtmp;

	listtmp = NULL;
	if (list)
	{
		if (list->nxt)
			listtmp = list->nxt;
		else
			listtmp = NULL;
		ft_freelist(list);
	}
	return (listtmp);
}
