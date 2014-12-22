/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 14:24:39 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/08 14:32:12 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void			*memory;
	size_t			c;
	unsigned char	*tmp;

	if (!size)
		return (NULL);
	c = 0;
	memory = (void *)malloc(sizeof(memory) * size);
	if (memory == NULL)
		return (NULL);
	tmp = (unsigned char *)memory;
	while (c <= size)
	{
		tmp[c] = 0;
		c++;
	}
	return (memory);
}
