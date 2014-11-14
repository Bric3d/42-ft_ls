/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 11:46:03 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/08 15:08:33 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t i2;
	size_t i3;

	i = 0;
	if (!src || !dst || size == 0)
		return (i);
	while (dst[i])
		i++;
	i3 = i;
	i2 = 0;
	while (src[i2])
	{
		if ((i < (size)) && (size > 0))
			dst[i] = src[i2];
		i++;
		i2++;
	}
	if (i3 > size)
	{
		return (i - (i3 - size));
	}
	dst[i] = '\0';
	return (i);
}
