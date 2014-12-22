/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 08:40:07 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/07 11:55:45 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int value;
	int is_neg;

	if (!str)
		return (0);
	is_neg = 1;
	value = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v' || *str == '\r'
		|| *str == '\f' || *str == ' ')
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		is_neg = -1;
		str++;
	}
	while (*str >= 48 && *str <= 57 && *str)
	{
		value = (value * 10) + (*str - 48);
		str++;
	}
	return (value * is_neg);
}
