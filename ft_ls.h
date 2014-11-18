/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 11:20:06 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/18 15:01:09 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

typedef struct	s_arg
{
	int l;
	int R;
	int a;
	int r;
	int t;
}				t_arg;

typedef struct	s_list
{
	struct	s_list	*prv;
	struct	s_list	*nxt;
	char			*name;
	int				sub;
}				t_list;

#endif
