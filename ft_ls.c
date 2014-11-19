/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 12:05:00 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/18 09:45:51 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/uio.h>
#include <unistd.h>
#include "libft.h"
#include <errno.h>

int ft_checkarg(char *str)
{
	int i;
	i = 0;
	while (str[i++])
	{
		if (str[i] != 'l' && str[i] != 'R' && str[i] != 'a' && str[i] != 'r'
				&& str[i] != 't')
			return (-str[i]);
	}
	return (1);
}

int ft_arg(t_arg *arg, char *str)
{
	int i;
	int b;
	if ((b = ft_checkarg(str)) < 0)
		return (b);
	i = 1;
	while (str[i])
	{
		if (str[i] == 'l')
			arg->l = 1;
		else if (str[i] == 'R')
			arg->R = 1;
		else if (str[i] == 'a')
			arg->a = 1;
		else if (str[i] == 'r')
			arg->r= 1;
		else if (str[i] == 't')
			arg->t = 1;
		i++;
	}
	return (0);
}

int ft_arguments(t_arg *arg, char **av)
{
	int i;
	int b;
	i = 1;
	while (av[i])
	{
		if (av[i][0] == '-')
		{
			if ((b =ft_arg(arg, av[i])) < 0)
			{
				errno = 60;
				return (b);
			}
		}
		else
			return (i);
		i++;
	}
	return (0);
}

int	ft_error(int i, char **av, char *str)
{
	ft_putstr(av[0]);
	ft_putstr(": ");
	if (errno == EACCES || errno == ENOENT)
	{
		ft_putstr(str);
		ft_putstr(": ");
		if (errno == EACCES)
			ft_putendl_fd("Permission denied", 2);
		if (errno == ENOENT)
			ft_putendl_fd("No such file or directory", 2);
	}
	if (errno == ENOTDIR)
		return (1);
	if (errno == 60)
	{
		ft_putstr_fd("illegal option -- ", 2);
		ft_putchar_fd(-i, 2);
		ft_putstr_fd("\nusage: ", 2);
		ft_putstr(av[0]);
		ft_putendl_fd(" [-alrtR] [file ...]", 2);
	}
	/*
	 * if (errno == )
	 * ft_putendl_fd("");
	 * if (errno == )
	 * ft_putendl_fd("");
	 */
	return (0);
}

t_list	*ft_createlistelem(void)
{
	t_list	*list;

	if ((list = ft_memalloc(sizeof(t_list))) == NULL)
		return (NULL);
	list->prv = NULL;
	list->nxt = NULL;
	list->name = NULL;
	list->sub = 0;
	return (list);
}

/*
 ** createlistelem-> Create a simple element of the list, put NULL everywhere.
 ** placebefore	--> PUT lis1 before list2. Want to place something after ?
 **					It's the same function dude. Yeah I know.
 ** placebetween  -> Put list between list1 and list2
 ** placeelement	 -> Take an un-implemented element list1 and an implemented
 **					element list2, and go back and forth in the chain to
 **					place list1 in the right place.
 */

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

t_list	*ft_placeelement(t_list *list1, t_list *list2)
{
	if (!list2)
		return(list1);
	while (list2->prv)
		list2 = list2->prv;
	while (ft_strcmp(list1->name, list2->name) > 0)
		list2 = list2->nxt;
	if (list2->prv == NULL && ft_strcmp(list1->name, list2->name) <= 0)
		ft_placebefore(list1, list2);
	else if (list2->nxt == NULL && ft_strcmp(list1->name, list2->name) >= 0)
		ft_placebefore(list2, list1);
	else
		ft_placebetween(list1, list2->prv, list2);
	return (list1);
}

int	main(int ac, char **av)
{
	int		i;
	DIR		*dir;
	t_arg	*arg;

	arg = ft_memalloc(sizeof(arg));
	i = ft_arguments(arg, av);
	if (i < ac && i > 0)
	{
		while (i <= ac - 1)
		{
			if ((dir = opendir(av[i++])))
				ft_diropen(dir, arg, av);
			else
				ft_error(i, av, av[i - 1]);
		}
	}
	else if (i >= 0 && (dir = opendir(".")))
		ft_diropen(dir, arg, av);
	else
		ft_error(i, av, NULL);
	return (0);
}
