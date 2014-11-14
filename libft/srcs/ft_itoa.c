/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 09:04:26 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/08 15:18:51 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_countno(char *buff, unsigned int pos, int n)
{
	if (n >= 10 || n <= -10)
	{
		if (n > 0)
			buff[pos] = (n % 10) + '0';
		else
			buff[pos] = -(n % 10) + '0';
		ft_countno(buff, pos - 1, n / 10);
	}
	else
	{
		if (n > 0)
			buff[pos] = n + '0';
		else
			buff[pos] = -n + '0';
	}
}

char	*ft_itoa(int n)
{
	char	*results;
	size_t	len;
	int		tn;

	tn = n;
	results = NULL;
	len = 1;
	while (tn /= 10)
		++len;
	if ((results = (char*)ft_memalloc(len + (n < 0 ? 2 : 1))) == NULL)
		return (NULL);
	if (n < 0)
	{
		results[0] = '-';
		ft_countno(&results[1], len - 1, n);
	}
	else
		ft_countno(results, len - 1, n);
	if (n < 0)
		results[len + 1] = 0;
	else
		results[len] = 0;
	return (results);
}
