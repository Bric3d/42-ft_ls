/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 16:50:44 by bbecker           #+#    #+#             */
/*   Updated: 2014/12/20 19:03:44 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_print_list_st(t_list *list, t_arg *arg, char *name)
{
	t_size	*size;
	int		n;

	n = 0;
	if (list && name && (name[0] != '.' || arg->a == 1 || arg->root == 1
		|| ft_strcmp(name, ".") == 0))
	{
		while (list->prv)
			list = list->prv;
		size = ft_calcsize(list, arg);
		ft_print_total(size, arg);
		while (list)
		{
			if (list->name[0] != '.' || arg->a == 1)
			{
				ft_print(size, list, arg);
				n++;
			}
			list = list->nxt;
		}
	}
	arg->root = 0;
	return (n);
}

int		ft_print_list_rev(t_list *list, t_arg *arg, char *name)
{
	t_size	*size;
	int		n;

	n = 0;
	if (list && name && (name[0] != '.' || arg->a == 1 || arg->root == 1
		|| ft_strcmp(name, ".") == 0))
	{
		size = ft_calcsize(list, arg);
		ft_print_total(size, arg);
		while (list->nxt)
			list = list->nxt;
		while (list)
		{
			if (list->name[0] != '.' || arg->a == 1)
			{
				ft_print(size, list, arg);
				n++;
			}
			list = list->prv;
		}
	}
	arg->root = 0;
	return (n);
}

int		ft_print_list(t_list *list, t_arg *arg, char *name)
{
	int n;

	n = 0;
	if (list && arg->r == 0)
		n = ft_print_list_st(list, arg, name);
	if (list && arg->r == 1)
		n = ft_print_list_rev(list, arg, name);
	return (n);
}

void	ft_print(t_size *size, t_list *list, t_arg *arg)
{
	if (arg->l == 1)
	{
		ft_print_rights(list->st_mode, list->sub);
		ft_print_int(size->linksize, list->nlink);
		ft_print_gn(list->username, size->usersize);
		ft_print_gn(list->groupname, size->groupsize);
		ft_print_int(size->size, list->st_size);
		ft_print_time(list->date);
	}
	ft_putstr(list->name);
	if (arg->l == 1)
		ft_disp_lnk(list);
	ft_putchar('\n');
}

int	ft_print_path(char *name, char *path, t_arg *arg, int ac)
{
	if (ac >= 2 && name && (name[0] != '.' || arg->a == 1))
	{
		ft_putstr(path);
		ft_putendl(":");
		return (1);
	}
	return (0);
}
