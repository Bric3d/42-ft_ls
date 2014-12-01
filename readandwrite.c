/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readandwrite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 17:05:24 by bbecker           #+#    #+#             */
/*   Updated: 2014/12/01 17:35:23 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list	*ft_list_read(struct dirent *entry, t_arg *arg, t_list *list, char *dr)
{
	t_list		*new;
	struct stat	*buf;

	if ((ft_strcmp(entry->d_name, "..") != 0
				&& ft_strcmp(entry->d_name, ".") != 0) || arg->a == 1)
	{
		new = ft_createlistelem();
		buf = (struct stat*)malloc(sizeof(struct stat));
		new->name = ft_strmalcpy(entry->d_name);
		if (new->name == NULL || buf == NULL)
		{
			ft_error(0, "malloc");
			exit(-1);
		}
		ft_write_path(dr, new);
		if (arg->rr == 1 || arg->t == 1 || arg->l == 1)
			ft_stat(new, buf, entry);
		if (arg->t == 0 && ((arg->l == 0 && arg->rr == 0) || new->sub != -1))
			list = ft_placeelement(new, list);
		else if (arg->t == 1 && new->sub != -1)
			list = ft_placelistent_d(new, list);
		free(buf);
	}
	return (list);
}

void	ft_write_path(char *prev, t_list *list)
{
	char	*tmp;

	if ((tmp = ft_strjoin(prev, "/")) == NULL)
	{
		ft_error(0, "Malloc");
		exit(-1);
	}
	if ((list->path = ft_strjoin(tmp, list->name)) == NULL)
	{
		ft_error(0, "Malloc");
		exit(-1);
	}
	free(tmp);
}
