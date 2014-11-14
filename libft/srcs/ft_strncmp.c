/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 13:51:28 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/06 14:31:03 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	c;
	unsigned int	b;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (-1);
	if (!s2)
		return (1);
	c = ft_strlen(s1);
	b = ft_strlen(s2);
	if (n > b)
		n = b + 1;
	if (n > c)
		n = c + 1;
	return (ft_memcmp(s1, s2, n));
}
