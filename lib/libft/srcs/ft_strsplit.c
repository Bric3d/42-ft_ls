/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 14:06:27 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/08 15:01:11 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_word_nb(char const *s, char c)
{
	size_t	a;
	size_t	numb;
	int		b;

	b = 0;
	a = 0;
	numb = 0;
	while (s[b])
	{
		if (s[b] != c && a == 0)
		{
			a = 1;
			numb++;
		}
		if (s[b] == c && a == 1)
			a = 0;
		b++;
	}
	return (numb);
}

void	ft_placestr(char **tab, char const *s, char c)
{
	int		a;
	int		start;
	int		b;

	b = 0;
	start = 0;
	a = 0;
	while (s[b])
	{
		if (s[b] != c && a == 0)
		{
			start = b;
			a = 1;
		}
		if (s[b] == c && a == 1)
		{
			*tab = ft_strsub(s, start, b - start);
			++tab;
			a = 0;
		}
		b++;
	}
	if (a == 1)
		*tab = ft_strsub(s, start, b - start);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**tab;
	size_t	nb;

	if (s == NULL)
		return (NULL);
	nb = ft_word_nb(s, c);
	tab = (char **)ft_memalloc(sizeof(char *) * (nb + 1));
	if (!tab)
		return (NULL);
	ft_placestr(tab, s, c);
	tab[nb] = '\0';
	nb = 0;
	return (tab);
}
