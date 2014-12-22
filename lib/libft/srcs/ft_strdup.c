/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 08:42:01 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/08 09:03:46 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char *ft_strdup(const char *s1)
{
	int		i;
	char	*duplicata;
	int		n;

	if (!s1)
		return (NULL);
	i = ft_strlen(s1);
	duplicata = (char *)malloc(sizeof(char *) * i);
	if (!duplicata)
		return (NULL);
	n = 0;
	while (n <= i)
	{
		duplicata[n] = s1[n];
		n++;
	}
	return (duplicata);
}
