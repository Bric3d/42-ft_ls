/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 12:05:00 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/30 16:43:31 by bbecker          ###   ########.fr       */
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
	int		b;

	arg = ft_memalloc(sizeof(arg));
	i = ft_arguments(arg, av);
	arg->root = 1;
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
