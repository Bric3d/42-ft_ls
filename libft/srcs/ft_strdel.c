/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 18:22:04 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/24 11:34:26 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

void	ft_strdel(char **as)
{
	int i;

	i = 0;
	if (as && *as)
	{
		while (as[i])
		{
			ft_bzero(as[i], ft_strlen(as[i]));
			free(as[i++]);
		}
		*as = NULL;
	}
}
