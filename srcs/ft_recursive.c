/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 16:52:30 by bbecker           #+#    #+#             */
/*   Updated: 2014/12/20 18:44:21 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	ft_recursiverev(t_list *list, t_arg *arg, int n)
{
	int c;

	c = 0;
	while (list->nxt)
		list = list->nxt;
	while (list)
	{
		if (list && list->sub == DT_DIR && ft_strcmp(list->name, "..") != 0
				&& ft_strcmp(list->name, ".") != 0)
			c = c + ft_list_dir(list->path, arg, 3, c + n);
		list = ft_free(list, arg->r);
	}
	return (0);
}

int	ft_recursive(t_list *list, t_arg *arg, int n)
{
	int c;

	c = 0;
	while (list->prv)
		list = list->prv;
	while (list)
	{
		if (list && list->sub == DT_DIR && ft_strcmp(list->name, "..") != 0
				&& ft_strcmp(list->name, ".") != 0)
			c = c + ft_list_dir(list->path, arg, 3, c + n);
		list = ft_free(list, arg->r);
	}
	return (c);
}

int	ft_recurchoice(t_list *list, t_arg *arg, int c)
{
	int n;

	n = 0;
	if (arg->rr == 1 && arg->r == 0)
		n = ft_recursive(list, arg, c + n);
	else if (arg->rr == 1 && arg->r == 1)
		n = ft_recursiverev(list, arg, c + n);
	else
		while (list)
			list = ft_free(list, arg->r);
	return (n);
}
