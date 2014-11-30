/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 16:43:52 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/30 16:44:21 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	ft_error(int i, char *str)
{
	if (errno == ENOTDIR)
		return (1);
	ft_putstr("ft_ls: ");
	if (errno == EACCES || errno == ENOENT)
	{
		if (str)
			perror(str);
		else
			perror("fts_open: ");
	}
	else if (errno == 1020)
	{
		ft_putstr_fd("illegal option -- ", 2);
		ft_putchar_fd(-i, 2);
		ft_putstr_fd("\nusage: ", 2);
		ft_putendl_fd("ft_ls [-alrtR] [file ...]", 2);
	}
	else
		perror(str);
	return (0);
}
