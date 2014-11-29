/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 12:05:00 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/29 20:03:39 by bbecker          ###   ########.fr       */
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
			arg->r= 1;
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
			if ((b =ft_arg(arg, av[i])) < 0)
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

t_list	*ft_createlistelem(void)
{
	t_list	*list;

	if ((list = ft_memalloc(sizeof(t_list))) == NULL)
	{
		ft_error(0, "Malloc");
		exit(-1);;
	}
	list->prv = NULL;
	list->nxt = NULL;
	list->name = NULL;
	list->sub = 0;
	return (list);
}

/*
 ** createlistelem-> Create a simple element of the list, put NULL everywhere.
 ** placebefore	--> PUT lis1 before list2. Want to place something after ?
 **					It's the same function dude. Yeah I know.
 ** placebetween  -> Put list between list1 and list2
 ** placeelement	 -> Take an un-implemented element list1 and an implemented
 **					element list2, and go back and forth in the chain to
 **					place list1 in the right place.
 */

void	ft_placebefore(t_list *list1, t_list *list2)
{
	list1->nxt = list2;
	list2->prv = list1;
}

void	ft_placebetween(t_list *list, t_list *list1, t_list *list2)
{
	list1->nxt = list;
	list->prv = list1;
	list->nxt = list2;
	list2->prv = list;
}

t_list	*ft_placelistent_da(t_list *list, t_list *list2)
{
	while (ft_strcmp(list->name, list2->name) > 0 && list->date == list2->date
			&& list2->nxt)
		list2 = list2->nxt;
	if (list2->prv == NULL && ft_strcmp(list->name, list2->name) <= 0)
		ft_placebefore(list, list2);
	else if (list2->nxt == NULL && ft_strcmp(list->name, list2->name) >= 0)
		ft_placebefore(list2, list);
	else
		ft_placebetween(list, list2->prv, list2);
	return (list);
}

t_list	*ft_placelistent_d(t_list *list, t_list *list2)
{
	if (!list2)
		return (list);
	while (list2->prv)
		list2 = list2->prv;
	while (list->date < list2->date && list2->nxt)
		list2 = list2->nxt;
	if (list2->prv == NULL && list->date > list2->date)
		ft_placebefore(list, list2);
	else if (list2->nxt == NULL && list->date < list2->date)
		ft_placebefore(list2, list);
	else if (list->date == list2->date)
		ft_placelistent_da(list, list2);
	else
		ft_placebetween(list, list2->prv, list2);
	return (list);
}

t_list	*ft_placeelement(t_list *list1, t_list *list2)
{
	if (!list2)
		return(list1);
	while (list2->prv)
		list2 = list2->prv;
	while (ft_strcmp(list1->name, list2->name) > 0 && list2->nxt)
		list2 = list2->nxt;
	if (list2->prv == NULL && ft_strcmp(list1->name, list2->name) <= 0)
		ft_placebefore(list1, list2);
	else if (list2->nxt == NULL && ft_strcmp(list1->name, list2->name) >= 0)
		ft_placebefore(list2, list1);
	else
		ft_placebetween(list1, list2->prv, list2);
	return (list1);
}

t_list	*ft_freerev(t_list	*list)
{
	t_list	*listtmp;

	listtmp = NULL;
	if (list)
	{
		if (list->prv)
			listtmp = list->prv;
		else
			listtmp = NULL;
		list->prv = NULL;
		list->nxt = NULL;
		free(list->name);
		free(list->path);
		list->sub = 0;
		list->date = 0;
		free(list);
	}
	return (listtmp);
}

t_list	*ft_free(t_list	*list)
{
	t_list	*listtmp;

	listtmp = NULL;
	if (list)
	{
		if (list->nxt)
			listtmp = list->nxt;
		else
			listtmp = NULL;
		list->prv = NULL;
		list->nxt = NULL;
		free(list->name);
		free(list->path);
		list->sub = 0;
		list->date = 0;
		free(list);
	}
	return (listtmp);
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

void	ft_isdir(t_list *list, struct dirent *dir)
{
	DIR	*directory

	if (list && dir)
	{
		if (dir->d_type == DT_DIR)
			list->sub = DT_DIR;
		else if (dir->d_type == DT_LNK)
			list->sub = DT_LNK;
		else if (dir->d_type == DT_CHR)
			list->sub = DT_CHR;
		else if (dir->d_type == DT_BLK)
			list->sub = DT_BLK;
		else if (dir->d_type == DT_SOCK)
			list->sub = DT_SOCK;
		else if (dir->d_type == DT_UNKNOWN)
			list->sub = DT_UNKNOWN;
		else
			list->sub = 0;
	}
}

void	ft_stat(t_list *new, struct stat *buf, struct dirent *dir)
{
	stat(new->path, buf);
	new->st_mode = buf->st_mode;
	ft_isdir(new, dir);
	if (new->sub == DT_DIR || new->sub == DT_LNK)
	{
		lstat(new->path, buf);
		new->st_mode = buf->st_mode;
	}
	new->date = buf->st_mtime;
	ft_getuid(new, buf->st_uid, buf->st_gid);
	new->st_size = buf->st_size;
	new->st_blocks = buf->st_blocks;
	new->nlink = buf->st_nlink;
}

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
		ft_stat(new, buf, entry);
		if (arg->t == 0)
			list = ft_placeelement(new, list);
		else if (arg->t == 1)
			list = ft_placelistent_d(new, list);
		free(buf);
	}
	return (list);
}

int	ft_recursiverev(t_list *list, t_arg *arg, char *name)
{
	while (list->nxt)
		list = list->nxt;
	while (list && list->prv)
	{
		if (list && list->sub == DT_DIR && ft_strcmp(list->name, "..") != 0
				&& ft_strcmp(list->name, ".") != 0)
		{
			if (name[0] != '.' || arg->a == 1)
				ft_putchar('\n');
			ft_list_dir(list->path, arg, 3, list->name);
		}
		list = ft_freerev(list);
	}
	if (list && list->sub == DT_DIR && ft_strcmp(list->name, "..") != 0
			&& ft_strcmp(list->name, ".") != 0)
	{
		if (name[0] != '.' || arg->a == 1)
			ft_putchar('\n');
		ft_list_dir(list->path, arg, 3, list->name);
		list = ft_freerev(list);
		free(list);
	}
	return (0);
}

int	ft_recursive(t_list *list, t_arg *arg, char *name)
{
	while (list->prv)
		list = list->prv;
	while (list->nxt)
	{
		if (list && list->sub == DT_DIR && ft_strcmp(list->name, "..") != 0
				&& ft_strcmp(list->name, ".") != 0)
		{
			if (name[0] != '.' || arg->a == 1)
				ft_putchar('\n');
			ft_list_dir(list->path, arg, 3, list->name);
		}
		list = ft_free(list);
	}
	if (list && list->sub == DT_DIR && ft_strcmp(list->name, "..") != 0
			&& ft_strcmp(list->name, ".") != 0)
	{
		if (name[0] != '.' || arg->a == 1)
			ft_putchar('\n');
		ft_list_dir(list->path, arg, 3, list->name);
		list = ft_free(list);
	}
	return (0);
}

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

void	ft_disp_lnk(t_list	*list)
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

void	ft_print(t_size *size, t_list *list, t_arg *arg)
{
	if (arg->l == 1)
	{
		ft_print_rights(list->st_mode, list->sub);
		ft_print_int(size->linksize, list->nlink);
		ft_print_gn(list->username, size->usersize);
		ft_print_gn(list->groupname, size->groupsize);
		ft_print_int(size->size, list->st_size);
		ft_print_time(list->date);
	}
	ft_putstr(list->name);
	if (arg->l == 1)
		ft_disp_lnk(list);
	ft_putchar('\n');
}

void	ft_print_time(time_t date)
{
	char	*str;
	char	**tab;

	str = ctime(&date);
	tab = ft_strsplit(str, ' ');
	ft_putstr(tab[1]);
	ft_putchar(' ');
	if (ft_strlen(tab[2]) < 2)
		ft_putchar(' ');
	ft_putstr(tab[2]);
	ft_putchar(' ');
	if ((time(0) - date) > 15778463 || ((time(0) - date) < 0))
		ft_putchar(' ');
	if ((time(0) - date) > 15778463 || ((time(0) - date) < 0))
		ft_putnstr(tab[4], 4);
	else
		ft_putnstr(tab[3], 5);
	ft_strdel(tab);
	ft_putchar(' ');
}

int		ft_usersize(t_list *list)
{
	int usersize;
	int i;

	usersize = 0;
	while (list->prv)
		list = list->prv;
	while (list->nxt)
	{
		i = ft_strlen(list->username);
		if (usersize < i)
			usersize = i;
		list = list->nxt;
	}
	i = ft_strlen(list->username);
	if (usersize < i)
		usersize = i;
	return (usersize);
}

int		ft_groupsize(t_list *list)
{
	int groupsize;
	int i;

	groupsize = 0;
	while (list->prv)
		list = list->prv;
	while (list->nxt)
	{
		i = ft_strlen(list->groupname);
		if (groupsize < i)
			groupsize = i;
		list = list->nxt;
	}
	i = ft_strlen(list->groupname);
	if (groupsize < i)
		groupsize = i;
	return (groupsize);
}

int	ft_linksize(t_list *list)
{
	int	maxsize;
	int	i;

	maxsize = 0;
	while (list->nxt)
	{
		i = ft_countnum(list->nlink);
		if (maxsize < i)
			maxsize = i;
		list = list->nxt;
	}
	i = ft_countnum(list->nlink);
	if (maxsize < i)
		maxsize = i;
	return (maxsize);
}

t_size	*ft_calcsize(t_list *list, t_arg *arg)
{
	t_size	*size;

	size = NULL;
	if (list && arg->l == 1)
	{
		if (!(size = (struct s_size*)ft_memalloc(sizeof(struct s_size))))
		{
			ft_error(0, "Malloc");
			return (NULL);
		}
		list = ft_maxsize(list, size);
		size->groupsize = ft_groupsize(list);
		size->usersize = ft_usersize(list);
		size->linksize = ft_linksize(list);
	}
	return (size);
}

t_list	*ft_maxsize(t_list *list, t_size *size)
{
	int		maxsize;
	int		i;
	t_list *first;

	maxsize = 0;
	while (list->prv)
		list = list->prv;
	first = list;
	while (list->nxt)
	{
		size->total = list->st_blocks + size->total;
		i = ft_countnum(list->st_size);
		if (maxsize < i)
			maxsize = i;
		list = list->nxt;
	}
	size->total = list->st_blocks + size->total;
	i = ft_countnum(list->st_size);
	if (maxsize < i)
		maxsize = i;
	size->size = maxsize;
	return (first);
}

void	ft_print_total(t_size *size, t_arg *arg)
{
	if (arg->l == 1)
	{
		ft_putstr("total ");
		ft_putnbr(size->total);
		ft_putchar('\n');
	}
}

int		ft_print_list_st(t_list *list, t_arg *arg, char *name)
{
	t_size	*size;

	if (list && name && (name[0] != '.' || arg->a == 1 || arg->root == 1))
	{
		while (list->prv)
			list = list->prv;
		size = ft_calcsize(list, arg);
		ft_print_total(size, arg);
		while (list->nxt)
		{
			if (list->name[0] != '.' || arg->a == 1)
				ft_print(size, list, arg);
			list = list->nxt;
		}
		if (list->name[0] != '.' || arg->a == 1)
			ft_print(size, list, arg);
	}
	arg->root = 0;
	return (0);
}

int		ft_print_list_rev(t_list *list, t_arg *arg, char *name)
{
	t_size	*size;

	if (list && name && (name[0] != '.' || arg->a == 1 || arg->root == 1))
	{
		size = ft_calcsize(list, arg);
		ft_print_total(size, arg);
		while (list->nxt)
			list = list->nxt;
		while (list->prv)
		{
			if (list->name[0] != '.' || arg->a == 1)
				ft_print(size, list, arg);
			list = list->prv;
		}
		if (list->name[0] != '.' || arg->a == 1)
			ft_print(size, list, arg);
	}
	arg->root = 0;
	return (0);
}

int	ft_print_list(t_list *list, t_arg *arg, char *name)
{
	if (list && arg->r == 0)
		ft_print_list_st(list, arg, name);
	if (list && arg->r == 1)
		ft_print_list_rev(list, arg, name);
	return (0);
}

int		ft_recurchoice(t_list *list, t_arg *arg, char *name)
{
	int ret;

	ret = 0;
	if (arg->rr == 1 && arg->r == 0)
		ret = ft_recursive(list, arg, name);
	else if (arg->rr == 1 && arg->r == 1)
		ret = ft_recursiverev(list, arg, name);
	else
		list = ft_freerev(list);
	return (ret);
}

void	ft_print_path(char *name, char *path, t_arg *arg, int ac)
{
	if (ac >= 2 && name && (name[0] != '.' || arg->a == 1))
	{
		ft_putstr(path);
		ft_putendl(":");
	}
}

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
	if((dir = ft_opendir(path, name)) == NULL)
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
	int b;

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
