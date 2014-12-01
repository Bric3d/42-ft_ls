/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directorystuff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 16:42:05 by bbecker           #+#    #+#             */
/*   Updated: 2014/12/01 18:55:50 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

DIR		*ft_opendir(char *path, char *name)
{
	DIR	*dir;

	if ((dir = opendir(path)) == NULL)
	{
		ft_error(0, name);
		return (NULL);
	}
	return (dir);
}

int		ft_closedir(DIR *dir, char *name)
{
	if ((closedir(dir)) == -1)
	{
		ft_error(0, name);
		return (-1);
	}
	else
		return (1);
}

int		ft_list_dir(char *path, t_arg *arg, int ac, char *name)
{
	DIR				*dir;
	struct dirent	*entry;
	t_list			*list;

	ft_print_path(name, path, arg, ac);
	if ((dir = ft_opendir(path, name)) == NULL)
		return (0);
	list = NULL;
	while ((entry = readdir(dir)))
		list = ft_list_read(entry, arg, list, path);
	if (ft_closedir(dir, name) != 1)
		return (-1);
	if (list)
		ft_print_list(list, arg, name);
	if (list)
		ft_recurchoice(list, arg, name);
	return (0);
}
