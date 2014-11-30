/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 11:20:06 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/30 15:26:53 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
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

# define DT_UNKNOWN	0
# define DT_FIFO	1
# define DT_CHR		2
# define DT_DIR		4
# define DT_BLK		6
# define DT_REG		8
# define DT_LNK		10
# define DT_SOCK	12
# define DT_WHT		14

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
	char			*username;
	char			*groupname;
	quad_t			st_blocks;
	off_t			st_size;
	mode_t			st_mode;
	nlink_t			nlink;
	time_t			date;
	int				sub;
}				t_list;

void	ft_freelist(t_list *list);
t_list	*ft_freerev(t_list	*list);
t_list	*ft_free(t_list	*list);
int	ft_error(int i, char *str);
int ft_checkarg(char *str);
int ft_arg(t_arg *arg, char *str);
int ft_arguments(t_arg *arg, char **av);
t_list	*ft_createlistelem(void);
void	ft_placebefore(t_list *list1, t_list *list2);
void	ft_placebetween(t_list *list, t_list *list1, t_list *list2);
t_list	*ft_placelistent_da(t_list *list, t_list *list2);
t_list	*ft_placelistent_d(t_list *list, t_list *list2);
t_list	*ft_placeelement(t_list *list1, t_list *list2);
void	ft_isdir(t_list *list, struct dirent *dir);
int		ft_maybedir(t_list *list);
int		ft_recurchoice(t_list *list, t_arg *arg, char *name);
int	ft_recursive(t_list *list, t_arg *arg, char *name);
int	ft_recursiverev(t_list *list, t_arg *arg, char *name);
int		ft_usersize(t_list *list);
int		ft_groupsize(t_list *list);
int	ft_linksize(t_list *list);
t_size	*ft_calcsize(t_list *list, t_arg *arg);
t_list	*ft_maxsize(t_list *list, t_size *size);
void	ft_getuid(t_list *new, uid_t st_uid, gid_t st_gid);
void	ft_stat(t_list *new, struct stat *buf, struct dirent *dir);
void	ft_print_path(char *name, char *path, t_arg *arg, int ac);
void	ft_print(t_size *size, t_list *list, t_arg *arg);
int	ft_print_list(t_list *list, t_arg *arg, char *name);
int		ft_print_list_rev(t_list *list, t_arg *arg, char *name);
int		ft_print_list_st(t_list *list, t_arg *arg, char *name);
void	ft_print_type(int sub);
void	ft_print_rights(mode_t st_mode, int sub);
void	ft_print_int(int size, unsigned int toprint);
void	ft_print_gn(char *name, int size);
void	ft_disp_lnk(t_list	*list);
void	ft_print_total(t_size *size, t_arg *arg);
void	ft_print_time(time_t date);
int		ft_list_dir(char *path, t_arg *arg, int ac, char *name);
int		ft_closedir(DIR *dir, char *name);
DIR		*ft_opendir(char *path, char *name);
char	*ft_get_name(char *str);
t_list	*ft_list_read(struct dirent *entry, t_arg *arg, t_list *list, char *dr);
void	ft_write_path(char *prev, t_list *list);


#endif
