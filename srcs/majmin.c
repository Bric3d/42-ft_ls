/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   majmin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/08 11:07:57 by bbecker           #+#    #+#             */
/*   Updated: 2014/12/22 16:18:04 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_majmin(t_list *list, t_size *size)
{
	int min;
	int maj;

	if (list->sub == DT_CHR || list->sub == DT_BLK)
	{
		min = ft_countnum(LS_MINOR(list->st_rdev));
		maj = ft_countnum(LS_MAJOR(list->st_rdev));
		while (maj++ < size->maj)
			ft_putchar(' ');
		ft_putnbr(LS_MAJOR(list->st_rdev));
		ft_putstr(",");
		while (min++ < size->min)
			ft_putchar(' ');
		ft_putnbr(LS_MINOR(list->st_rdev));
		ft_putchar(' ');
	}
}

void	ft_calcmm(t_list *list, t_size *size)
{
	int	i;

	size->maj = 3;
	size->min = 4;
	i = 0;
	while (list)
	{
		if (list->sub == DT_CHR || list->sub == DT_BLK)
		{
			i = ft_countnum(LS_MINOR(list->st_rdev));
			if (i > size->min)
				size->min = i;
			i = ft_countnum(LS_MAJOR(list->st_rdev));
			if (i > size->maj)
				size->maj = i;
			i = size->min + size->maj + 1;
			if (i > size->size)
				size->size = i;
		}
		list = list->nxt;
	}
}
