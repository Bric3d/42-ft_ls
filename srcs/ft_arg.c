/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 16:44:56 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/30 16:46:48 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
			arg->rr = 1;
		else if (str[i] == 'a')
			arg->a = 1;
		else if (str[i] == 'r')
			arg->r = 1;
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
			if ((b = ft_arg(arg, av[i])) < 0)
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
