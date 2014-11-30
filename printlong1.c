/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printlong1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 16:48:58 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/30 16:49:48 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_type(int sub)
{
	ft_putnbr(sub);
	ft_putchar(' ');
	if (sub == DT_DIR)
		ft_putchar('d');
	else if (sub == DT_LNK)
		ft_putchar('l');
	else if (sub == DT_BLK)
		ft_putchar('b');
	else if (sub == DT_CHR)
		ft_putchar('c');
	else if (sub == DT_SOCK)
		ft_putchar('s');
	else if (sub == DT_FIFO)
		ft_putchar('p');
	else if (sub == DT_REG)
		ft_putchar('-');
	else
		ft_putchar('?');
}

void	ft_print_rights(mode_t st_mode, int sub)
{
	ft_print_type(sub);
	ft_putchar((st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((st_mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((st_mode & S_IXOTH) ? 'x' : '-');
	ft_putstr("  ");
}

void	ft_print_int(int size, unsigned int toprint)
{
	int n;

	n = size - ft_countnum(toprint);
	while (n-- > 0)
		ft_putchar(' ');
	ft_putnbr(toprint);
	ft_putchar(' ');
}

void	ft_print_gn(char *name, int size)
{
	int n;

	n = size - ft_strlen(name);
	ft_putstr(name);
	while (n-- > 0)
		ft_putchar(' ');
	ft_putstr("  ");
}

void	ft_disp_lnk(t_list *list)
{
	char	*lnkcontent;
	int		ret;
	int		size;

	if (list->sub == DT_LNK)
	{
		size = 1024;
		lnkcontent = (char *)ft_memalloc(sizeof(char) * (size));
		if (!lnkcontent)
		{
			ft_error(0, "Malloc");
			exit(-1);
		}
		ret = readlink(list->path, lnkcontent, size);
		lnkcontent[ret] = '\0';
		ft_putstr(" -> ");
		ft_putstr(lnkcontent);
		ft_strsupr(lnkcontent, size);
	}
}
