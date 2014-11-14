/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 17:17:05 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/14 19:32:49 by bbecker          ###   ########.fr       */
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
	if (!str)
		str = ft_strjoin(str, "fts_open");
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

int	ft_dirstat(DIR *dir, t_arg *arg, char **av)
{
	struct dirent *drn;

	while((drn = readdir(dir)) != NULL)
		if (drn->d_name[0] != '.' || arg->a == 1)
			ft_putendl(drn->d_name);
	if (closedir(dir) == -1)
		ft_error(0, av, NULL);
	return (0);
}

//int ft_dirwork

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
				ft_dirstat(dir, arg, av);
			else
				ft_error(i, av, av[i - 1]);
		}
	}
	else if (i >= 0 && (dir = opendir(".")))
		ft_dirstat(dir, arg, av);
	else
		ft_error(i, av, NULL);
	return (0);
}
