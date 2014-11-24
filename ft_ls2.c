/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 12:05:00 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/23 17:52:06 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <unistd.h>
#include "libft.h"
#include <errno.h>
#include <stdlib.h>

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
				errno = 1020;
				return (b);
			}
		}
		else
			return (i);
		i++;
	}
	return (0);
}

int	ft_error(int i, char *str)
{
	ft_putstr("ft_ls: ");
	if (errno == EACCES || errno == ENOENT)
	{
		if (str)
			perror(str);
		else
			perror("fts_open: ");
		/*ft_putstr("fts_open");
		ft_putstr(": ");
		//perror(str);
		if (errno == EACCES)
			ft_putendl_fd("Permission denied", 2);
		if (errno == ENOENT)
			ft_putendl_fd("No such file or directory", 2);*/
	}
	else if (errno == ENOTDIR)
		return (1);
	else if (errno == 1020)
	{
		ft_putstr_fd("illegal option -- ", 2);
		ft_putchar_fd(-i, 2);
		ft_putstr_fd("\nusage: ", 2);
		ft_putendl_fd("ft_ls [-alrtR] [file ...]", 2);
	}
	else
		perror(str);
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

t_list	*ft_placelistent_da(t_list *list, t_list *list2)
{
	while (ft_strcmp(list->name, list2->name) > 0 && list->date == list2->date
			&& list2->nxt)
		list2 = list2->nxt;
	if (list2->prv == NULL && ft_strcmp(list->name, list2->name) <= 0)
		ft_placebefore(list, list2);
	else if (list2->nxt == NULL && ft_strcmp(list->name, list2->name) >= 0)
		ft_placebefore(list2, list);
	else
		ft_placebetween(list, list2->prv, list2);
	return (list);
}

t_list	*ft_placelistent_d(t_list *list, t_list *list2)
{
	if (!list2)
		return (list);
	while (list2->prv)
		list2 = list2->prv;
	while (list->date < list2->date && list2->nxt)
		list2 = list2->nxt;
	if (list2->prv == NULL && list->date > list2->date)
		ft_placebefore(list, list2);
	else if (list2->nxt == NULL && list->date < list2->date)
		ft_placebefore(list2, list);
	else if (list->date == list2->date)
		ft_placelistent_da(list, list2);
	else
		ft_placebetween(list, list2->prv, list2);
	return (list);
}

t_list	*ft_placeelement(t_list *list1, t_list *list2)
{
	if (!list2)
		return(list1);
	while (list2->prv)
		list2 = list2->prv;
	while (ft_strcmp(list1->name, list2->name) > 0 && list2->nxt)
		list2 = list2->nxt;
	if (list2->prv == NULL && ft_strcmp(list1->name, list2->name) <= 0)
		ft_placebefore(list1, list2);
	else if (list2->nxt == NULL && ft_strcmp(list1->name, list2->name) >= 0)
		ft_placebefore(list2, list1);
	else
		ft_placebetween(list1, list2->prv, list2);
	return (list1);
}

t_list	*ft_freerev(t_list	*list)
{
	t_list	*listtmp;

	listtmp = NULL;
	if (list)
	{
		if (list->prv)
			listtmp = list->prv;
		else
			listtmp = NULL;
		list->prv = NULL;
		list->nxt = NULL;
		free(list->name);
		free(list->path);
		list->sub = 0;
		list->date = 0;
		free(list);
	}
	return (listtmp);
}



t_list	*ft_free(t_list	*list)
{
	t_list	*listtmp;

	listtmp = NULL;
	if (list)
	{
		if (list->nxt)
			listtmp = list->nxt;
		else
			listtmp = NULL;
		list->prv = NULL;
		list->nxt = NULL;
		free(list->name);
		free(list->path);
		list->sub = 0;
		list->date = 0;
		free(list);
	}
	return (listtmp);
}

void	ft_isdir(t_list *list)
{
	DIR	*dir;

	errno = 0;
	if (list)
		{
		if ((dir = opendir(list->path)) == NULL)
		{
			if (errno == ENOTDIR)
				list->sub = 0;
			else
				list->sub = 1;
		}
		else
		{
			list->sub = 1;
			closedir(dir);
		}
		if (list->st_mode == S_IFLNK)
			list->sub = 0;
	}
}

void	ft_write_path(char *prev, t_list *list)
{
	char	*tmp;
	char	*tmp2;

	//	if (prev[0] != '.' && prev[1] != '/')
	//	{
	tmp2 = ft_strjoin("./", prev);
	tmp = ft_strjoin(prev, "/");
	list->path = ft_strjoin(tmp, list->name);
	free(tmp);
	free(tmp2);
	/*	}
		else
		{
		tmp = ft_strjoin(prev, "/");
		list->path = ft_strjoin(tmp, list->name);
		free(tmp);
		}*/
}

t_list	*ft_list_read(struct dirent *entry, t_arg *arg, t_list *list, char *dr)
{
	t_list		*new;
	struct stat	*buf;

	new = ft_createlistelem();
	new->name = (char*)ft_memalloc(ft_strlen(entry->d_name));
	buf = (struct stat*)malloc(sizeof(struct stat));
	if (new->name == NULL || buf == NULL)
	{
		ft_error(0, "malloc");
		return (NULL);
	}
	ft_strcpy(new->name, entry->d_name);
	ft_write_path(dr, new);
	stat(new->path, buf);
	new->date = buf->st_mtime;
	new->st_mode = buf->st_mode;
	ft_isdir(new);
	if (arg->t == 0)
		list = ft_placeelement(new, list);
	else if (arg->t == 1)
		list = ft_placelistent_d(new, list);
	free(buf);
	return (list);
}

int	ft_recursiverev(t_list *list, t_arg *arg, char *name)
{
	while (list->nxt)
		list = list->nxt;
	while (list && list->prv)
	{
		if (list->sub == 1 && ft_strcmp(list->name, "..") != 0
				&&	ft_strcmp(list->name, ".") != 0)
		{
			if (name[0] != '.' || arg->a == 1)
				ft_putchar('\n');
			ft_list_dir(list->path, arg, 3, list->name);
		}
		list = ft_freerev(list);
	}
	if (list->sub == 1 && ft_strcmp(list->name, "..") != 0
			&&	ft_strcmp(list->name, ".") != 0 && list)
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
		if (list->sub == 1 && ft_strcmp(list->name, "..") != 0
				&&	ft_strcmp(list->name, ".") != 0)
		{
			if (name[0] != '.' || arg->a == 1)
				ft_putchar('\n');
			ft_list_dir(list->path, arg, 3, list->name);
		}
		list = ft_free(list);
	}
	if (list->sub == 1 && ft_strcmp(list->name, "..") != 0
			&&	ft_strcmp(list->name, ".") != 0)
	{
		if (name[0] != '.' || arg->a == 1)
			ft_putchar('\n');
		ft_list_dir(list->path, arg, 3, list->name);
		list = ft_free(list);
	}
	return (0);
}

int	ft_print_list_st(t_list *list, t_arg *arg, char *name)
{
	if (list && name && (name[0] != '.' || arg->a == 1))
	{
		while (list->prv && arg->r == 0)
			list = list->prv;
		while (list->nxt && arg->r == 0)
		{
			if (list->name[0] != '.' || arg->a == 1)
				ft_putendl(list->name);
			list = list->nxt;
		}
		if (list->name[0] != '.' || arg->a == 1)
		ft_putendl(list->name);
	}
	return (0);
}

int	ft_print_list_rev(t_list *list, t_arg *arg, char *name)
{
	if (list && name && (name[0] != '.' || arg->a == 1))
	{
		while (list->nxt && arg->r == 1)
			list = list->nxt;
		while (list->prv && arg->r == 1)
		{
			if (list->name[0] != '.' || arg->a == 1)
				ft_putendl(list->name);
			list = list->prv;
		}
		if (list->name[0] != '.' || arg->a == 1)
			ft_putendl(list->name);
	}
	return (0);
}

int	ft_print_list(t_list *list, t_arg *arg, char *name)
{
	if (list && arg->r == 0)
		ft_print_list_st(list, arg, name);
	if (list && arg->r == 1)
		ft_print_list_rev(list, arg, name);
	return (0);
}

int	ft_recurchoice(t_list *list, t_arg *arg, char *name)
{
	int ret;

	ret = 0;
	if (arg->R == 1 && arg->r == 0)
		ret = ft_recursive(list, arg, name);
	else if (arg->R == 1 && arg->r == 1)
		ret = ft_recursiverev(list, arg, name);
	return (ret);
}

int		ft_list_dir(char *path, t_arg *arg, int ac, char *name)
{
	DIR				*dir;
	struct dirent	*entry;
	t_list			*list;

	if (ac >= 2 && name && (name[0] != '.' || arg->a == 1))
	{
		ft_putstr(path);
		ft_putendl(":");
	}
	list = NULL;
	if ((dir = opendir(path)) == NULL)
	{
		ft_error(0, name);
		return (0);
	}
	while ((entry = readdir(dir)))
		list = ft_list_read(entry, arg, list, path);
	if ((closedir(dir)) == -1 || list == NULL)
	{
		ft_error(0, name);
		return (-1);
	}
	ft_print_list(list, arg, name);
	ft_recurchoice(list, arg, name);
	return (0);
}

char	*ft_get_name(char *str)
{
	int i;

	i = ft_strlen(str) - 1;
	while (str[i])
	{
		if (str[i] == '/')
			return (&str[i + 1]);
		i--;
	}
	return (str);
}

int		main(int ac, char **av)
{
	int		i;
	t_arg	*arg;
	int b;

	arg = ft_memalloc(sizeof(arg));
	i = ft_arguments(arg, av);
	b = i;
	if (i < ac && i > 0 && arg != NULL)
	{
		while (i < ac)
		{
			ft_list_dir(av[i], arg, ac - b, ft_get_name(av[i]));
			i++;
			if (ac - b >= 2)
				ft_putchar('\n');
		}
	}
	else if (i >= 0 && arg != NULL)
		ft_list_dir(".", arg, 0, ".");
	else if (i < 0)
		ft_error(i, NULL);
	else
		ft_error(0, "malloc");
	return (0);
}
