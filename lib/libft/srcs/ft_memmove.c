/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 17:37:45 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/05 17:16:49 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void *ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned char	*s3;
	size_t			i;

	s3 = (unsigned char*)malloc(sizeof(unsigned char*) * len);
	if (s3 == NULL)
		return (NULL);
	s1 = (unsigned char *)dst;
	s2 = (unsigned char *)src;
	i = 0;
	while (i < len)
	{
		s3[i] = s2[i];
		i++;
	}
	i = 0;
	while (i < len)
	{
		s1[i] = s3[i];
		i++;
	}
	return (s1);
}
