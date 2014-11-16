/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 11:20:06 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/16 17:17:34 by bbecker          ###   ########.fr       */
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
	struct t_list	*prv;
	struct t_list	*nxt;
	char			*name;
	int				sub;
}				t_list;

#endif
