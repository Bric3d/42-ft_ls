/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 16:06:54 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/04 16:53:30 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	char	*tmp1;
	char	*tmp2;
	int		i;
	int		c;

	tmp1 = (char *)s1;
	tmp2 = (char *)s2;
	i = 0;
	c = 0;
	if (tmp2[0] == '\0')
		return (tmp1);
	while (tmp1[i])
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
