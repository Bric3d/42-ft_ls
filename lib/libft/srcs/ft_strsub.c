/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 15:34:14 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/12 19:53:21 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*data;
	unsigned int	c;

	if (s == NULL)
		return (NULL);
	data = (char *)ft_memalloc(sizeof(char) * len + 1);
	if (data == NULL)
		return (NULL);
	c = 0;
	while (c < (unsigned int)len && s[c + start])
	{
		data[c] = s[c + start];
		c++;
	}
	data[c] = '\0';
	return (data);
}
