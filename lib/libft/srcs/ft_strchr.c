/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 14:26:01 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/06 11:00:47 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strchr(const char *s, int c)
{
	char	*tmp;
	char	car;
	size_t	i;

	tmp = (char *)s;
	car = (char)c;
	i = 0;
	while (i < (ft_strlen(tmp) + 1))
	{
		if (tmp[i] == car)
		{
			return (&tmp[i]);
		}
		i++;
	}
	return (NULL);
}
