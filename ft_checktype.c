/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checktype.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 17:07:02 by bbecker           #+#    #+#             */
/*   Updated: 2014/12/01 18:47:13 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_maybedir(t_list *list)
{
	if (S_ISLNK(list->st_mode))
		return (DT_LNK);
	if (S_ISREG(list->st_mode))
		return (DT_REG);
	if (S_ISCHR(list->st_mode))
		return (DT_CHR);
	if (S_ISBLK(list->st_mode))
		return (DT_BLK);
	if (S_ISFIFO(list->st_mode))
		return (DT_FIFO);
	if (S_ISSOCK(list->st_mode))
		return (DT_SOCK);
	if (S_ISDIR(list->st_mode))
		return (DT_DIR);
	else
		return (DT_UNKNOWN);
}

void	ft_isdir(t_list *list, struct dirent *dir)
{
	DIR *directory;

	if (list && dir)
	{
		if (dir->d_type == DT_LNK)
			list->sub = DT_LNK;
		else if (dir->d_type == DT_DIR)
			list->sub = DT_DIR;
		else if (dir->d_type == DT_CHR)
			list->sub = DT_CHR;
		else if (dir->d_type == DT_BLK)
			list->sub = DT_BLK;
		else if (dir->d_type == DT_SOCK)
			list->sub = DT_SOCK;
		else
		{
			if ((list->sub = ft_maybedir(list)) != DT_UNKNOWN)
				return ;
			else if ((directory = opendir(list->path)))
			{
				list->sub = DT_DIR;
				closedir(directory);
			}
		}
	}
}
