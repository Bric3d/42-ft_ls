/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 11:20:06 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/28 18:54:29 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include "ft_ls.h"
# include <dirent.h>
# include <sys/types.h>
# include <sys/dir.h>
# include <sys/uio.h>
# include <grp.h>
# include <pwd.h>
# include <sys/stat.h>
# include <unistd.h>
# include "libft.h"
# include <errno.h>
# include <stdlib.h>
# include <time.h>
# include <stdio.h>

typedef struct	s_arg
{
	int l;
	int rr;
	int a;
	int r;
	int t;
	int root;
}				t_arg;

typedef struct	s_size
{
	quad_t	total;
	int		size;
	int		groupsize;
	int		usersize;
	int		linksize;
}				t_size;

typedef struct	s_list
{
	struct	s_list	*prv;
	struct	s_list	*nxt;
	char			*name;
	char			*path;
	nlink_t			nlink;
	time_t			date;
	quad_t			st_blocks;
	mode_t			st_mode;
	off_t			st_size;
	char			*username;
	char			*groupname;
	int				sub;
}				t_list;

int		ft_list_dir(char *path, t_arg *arg, int ac, char *name);
int		ft_print_list(t_list *list, t_arg *arg, char *name);
t_list	*ft_list_read(struct dirent *entry, t_arg *arg, t_list *list, char *dr);
void	ft_write_path(char *prev, t_list *list);
t_list	*ft_placeelement(t_list *list1, t_list *list2);
t_list	*ft_placelistent_d(t_list *list, t_list *list2);
t_list	*ft_placelistent_da(t_list *list, t_list *list2);
void	ft_placebetween(t_list *list, t_list *list1, t_list *list2);
void	ft_placebefore(t_list *list1, t_list *list2);
t_list	*ft_createlistelem(void);
int		ft_arguments(t_arg *arg, char **av);
int		ft_arg(t_arg *arg, char *str);
int		ft_checkarg(char *str);
int		ft_recursive(t_list *list, t_arg *arg, char *name);
void	ft_print_time(time_t date);
t_list	*ft_maxsize(t_list *list, t_size *size);

#endif
