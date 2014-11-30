/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 16:52:30 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/30 16:53:15 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	ft_recursiverev(t_list *list, t_arg *arg, char *name)
{
	while (list->nxt)
		list = list->nxt;
	while (list && list->prv)
	{
		if (list && list->sub == DT_DIR && ft_strcmp(list->name, "..") != 0
				&& ft_strcmp(list->name, ".") != 0)
		{
			if (name[0] != '.' || arg->a == 1)
				ft_putchar('\n');
			ft_list_dir(list->path, arg, 3, list->name);
		}
		list = ft_freerev(list);
	}
	if (list && list->sub == DT_DIR && ft_strcmp(list->name, "..") != 0
			&& ft_strcmp(list->name, ".") != 0)
	{
		if (name[0] != '.' || arg->a == 1)
			ft_putchar('\n');
		ft_list_dir(list->path, arg, 3, list->name);
		list = ft_freerev(list);
		free(list);
	}
	return (0);
}

int	ft_recursive(t_list *list, t_arg *arg, char *name)
{
	while (list->prv)
		list = list->prv;
	while (list->nxt)
	{
		if (list && list->sub == DT_DIR && ft_strcmp(list->name, "..") != 0
				&& ft_strcmp(list->name, ".") != 0)
		{
			if (name[0] != '.' || arg->a == 1)
				ft_putchar('\n');
			ft_list_dir(list->path, arg, 3, list->name);
		}
		list = ft_free(list);
	}
	if (list && list->sub == DT_DIR && ft_strcmp(list->name, "..") != 0
			&& ft_strcmp(list->name, ".") != 0)
	{
		if (name[0] != '.' || arg->a == 1)
			ft_putchar('\n');
		ft_list_dir(list->path, arg, 3, list->name);
		list = ft_free(list);
	}
	return (0);
}

int	ft_recurchoice(t_list *list, t_arg *arg, char *name)
{
	int ret;

	ret = 0;
	if (arg->rr == 1 && arg->r == 0)
		ret = ft_recursive(list, arg, name);
	else if (arg->rr == 1 && arg->r == 1)
		ret = ft_recursiverev(list, arg, name);
	else
		list = ft_freerev(list);
	return (ret);
}
