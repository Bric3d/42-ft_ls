/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 09:34:29 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/06 10:10:39 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*data;

	if (!s && !f)
		return (NULL);
	data = (char*)ft_memalloc(sizeof(char *) * ft_strlen(s) + 1);
	if (!data)
		return (NULL);
	i = 0;
	while (s[i])
	{
		data[i] = (*f)(i, s[i]);
		i++;
	}
	data[i] = '\0';
	return (data);
}
