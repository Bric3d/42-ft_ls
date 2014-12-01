/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 16:57:45 by bbecker           #+#    #+#             */
/*   Updated: 2014/12/01 18:19:37 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list	*ft_createlistelem(void)
{
	t_list	*list;

	if ((list = ft_memalloc(sizeof(t_list))) == NULL)
	{
		ft_error(0, "Malloc");
		exit(-1);
	}
	list->prv = NULL;
	list->nxt = NULL;
	list->name = NULL;
	list->sub = 0;
	return (list);
}

void	ft_placebefore(t_list *list1, t_list *list2)
{
	list1->nxt = list2;
	list2->prv = list1;
}

void	ft_placebetween(t_list *list, t_list *list1, t_list *list2)
{
	list1->nxt = list;
	list->prv = list1;
	list->nxt = list2;
	list2->prv = list;
}

t_list	*ft_listmove(t_list *list, int r)
{
	if (r == 1)
		list = list->prv;
	if (r == 0)
		list = list->nxt;
	return (list);
}

t_list	*ft_rewindnff(t_list *list, int r)
{
	if (list)
	{
		while (r == 1 && list->nxt)
			list = list->nxt;
		while (r == 0 && list->prv)
			list = list->prv;
	}
	return (list);
}
