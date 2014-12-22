/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 11:23:22 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/06 12:03:35 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	unsigned int i;
	unsigned int c;

	i = 0;
	c = 0;
	while (s1[i])
		i++;
	while (s2[c] && c < n)
	{
		s1[i + c] = s2[c];
		c++;
	}
	s1[i + c] = '\0';
	return (s1);
}
