/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 16:41:45 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/08 12:13:53 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	char	*tmp1;
	char	*tmp2;
	size_t	i;
	size_t	c;

	tmp1 = (char *)s1;
	tmp2 = (char *)s2;
	i = 0;
	c = 0;
	if (tmp2[0] == '\0')
		return (tmp1);
	while (tmp1[i] && i < n)
	{
		if (tmp1[i] == tmp2[c])
			c++;
		else
			c = 0;
		if (tmp2[c] == '\0')
			return (&tmp1[i - c + 1]);
		i++;
	}
	return (NULL);
}
