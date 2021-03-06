/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stats.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 17:17:49 by bbecker           #+#    #+#             */
/*   Updated: 2014/12/22 12:43:29 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/stat.h>

void	ft_getuid(t_list *new, uid_t st_uid, gid_t st_gid)
{
	struct passwd	*passwd;
	struct group	*group;

	errno = 0;
	passwd = getpwuid(st_uid);
	group = getgrgid(st_gid);
	if (!passwd)
		new->username = ft_itoa(st_uid);
	else
		new->username = ft_strmalcpy(passwd->pw_name);
	if (!group)
		new->groupname = ft_itoa(st_gid);
	else
		new->groupname = ft_strmalcpy(group->gr_name);
}

void	ft_stat(t_list *new, struct stat *buf, struct dirent *dir)
{
	if (lstat(new->path, buf) == -1)
	{
		ft_error(0, new->name);
		new->sub = -1;
		return ;
	}
	new->st_mode = buf->st_mode;
	ft_isdir(new, dir);
	new->date = buf->st_mtime;
	ft_getuid(new, buf->st_uid, buf->st_gid);
	new->st_size = buf->st_size;
	new->st_rdev = buf->st_rdev;
	new->st_blocks = buf->st_blocks;
	new->nlink = buf->st_nlink;
}
