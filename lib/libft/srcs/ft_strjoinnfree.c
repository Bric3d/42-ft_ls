/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinnfree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 11:41:44 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/20 11:42:31 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinnfree(char *s1, char *s2)
{
	size_t	b;
	size_t	c;
	char	*data;
	size_t	d;

	b = strlen (s1);
	c = strlen (s2);
	data = (char *)ft_memalloc(sizeof(char) * (b + c + 1));
	d = 0;
	while (d < b && s1[d])
	{
		data[d] = s1[d];
		d++;
	}
	d = 0;
	while (d < c && s2[d])
	{
		data[d + b] = s2[d];
		d++;
	}
	data[b + c + 1] = '\0';
	free(s1);
	free(s2);
	return (data);
}
