/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 08:33:56 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/08 12:17:09 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	a;
	size_t	b;
	char	*s2;

	a = 0;
	b = 0;
	if (!s)
		return (NULL);
	s2 = (char *)ft_memalloc(sizeof(char) * strlen(s) + 1);
	if (s2 == NULL)
		return (NULL);
	while (ft_isblank(s[a]) == 1)
		a++;
	while (s[a])
		s2[b++] = s[a++];
	while (ft_isblank(s2[--b]) == 1)
		s2[b] = '\0';
	return (s2);
}
