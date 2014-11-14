/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 15:12:31 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/06 11:38:17 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strrchr(const char *s, int c)
{
	char			*tmp;
	char			car;
	unsigned int	i;
	int				j;

	tmp = (char *)s;
	car = (char)c;
	i = 0;
	j = -1;
	while (i < (ft_strlen(tmp) + 1))
	{
		if (tmp[i] == car)
		{
			j = (int)i;
		}
		i++;
	}
	if (j != -1)
		return (&tmp[j]);
	return (NULL);
}
