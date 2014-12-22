/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/02 10:31:42 by bbecker           #+#    #+#             */
/*   Updated: 2014/12/20 18:53:24 by bbecker          ###   ########.fr       */
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
	new->path = ft_strmalcpy(av);
	ft_stat(new, buf, NULL);
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

void	ft_read_arg(t_list *list, t_arg *arg, int ac, int i)
{
	t_size	*size;
	t_list	*listtmp;
	int		c;

	c = 0;
	listtmp = list;
	size = ft_calcsize(list, arg);
	while (list)
	{
		if (list->sub != DT_DIR)
			ft_print(size, list, arg), c++;
		list = ft_listmove(list, arg->r);
	}
	list = listtmp;
	while (list)
	{
		if (c != 0 && list->sub == DT_DIR)
			ft_putchar('\n');
		if (list->sub == DT_DIR)
			ft_list_dir(list->name, arg, ac - i, 0), c++;
		list = ft_free(list, arg->r);
	}
	free(size);
}

int		main(int ac, char **av)
{
	int		i;
	t_arg	*arg;
	t_list	*list;

	arg = ft_memalloc(sizeof(arg));
	i = ft_arguments(arg, av);
	if (i < ac && i > 0 && arg != NULL)
	{
		arg->root = 1;
		list = ft_sort_arg(av, i, arg);
		ft_read_arg(list, arg, ac, i);
	}
	else if (i >= 0 && arg != NULL)
		ft_list_dir(".", arg, 0, 0);
	if (i < 0 || arg == NULL)
		ft_error(i, "Malloc");
	if (arg != NULL)
		free(arg);
	return (0);
}
