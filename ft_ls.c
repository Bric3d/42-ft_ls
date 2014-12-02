/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/02 10:31:42 by bbecker           #+#    #+#             */
/*   Updated: 2014/12/02 10:32:31 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

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

t_list	*ft_createlistarg(char *av, t_list *list, struct stat *buf, t_arg *arg)
{
	t_list		*new;

	new = ft_createlistelem();
	if (!new)
	{
		ft_error(0, "Malloc");
		exit(-1);
	}
	new->name = ft_strmalcpy(av);
	new->date = buf->st_mtime;
	if (arg->t == 0)
		list = ft_placeelement(new, list);
	if (arg->t == 1)
		list = ft_placelistent_d(new, list);
	return (list);
}

t_list	*ft_sort_arg(char **av, int i, t_arg *arg)
{
	struct stat	*buf;
	t_list		*list;

	list = NULL;
	if (av[i])
	{
		buf = (struct stat*)malloc(sizeof(struct stat));
		if (!buf)
			ft_error(0, "Malloc");
		if (!buf)
			exit(-1);
		while (av[i])
		{
			if (stat(av[i], buf) == -1)
				ft_error(0, av[i]);
			else
				list = ft_createlistarg(av[i], list, buf, arg);
			i++;
		}
		free(buf);
	}
	list = ft_rewindnff(list, arg->r);
	return (list);
}

int		main(int ac, char **av)
{
	int		i;
	t_arg	*arg;
	t_list	*list;

	arg = ft_memalloc(sizeof(arg));
	i = ft_arguments(arg, av);
	arg->root = 1;
	if (i < ac && i > 0 && arg != NULL)
	{
		list = ft_sort_arg(av, i, arg);
		while (list)
		{
			ft_list_dir(list->name, arg, ac - i, ft_get_name(list->name));
			list = ft_listmove(list, arg->r);
			if (ac - i >= 2)
				ft_putchar('\n');
		}
	}
	else if (i >= 0 && arg != NULL)
		ft_list_dir(".", arg, 0, ".");
	if (i < 0 || arg == NULL)
		ft_error(i, "Malloc");
	if (arg != NULL)
		free(arg);
	return (0);
}
