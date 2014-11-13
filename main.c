/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 17:17:05 by bbecker           #+#    #+#             */
/*   Updated: 2014/11/13 20:00:14 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/uio.h>
#include <unistd.h>
#include "libft.h"

int	main(int ac, char **av)
{
	int i;
	DIR *dir;
	struct dirent *drn;
	int b;

	b = 0;
	i = 1;
	if (ac> 1)
	{
		while (i <= ac - 1)
		{
			if ((dir = opendir(av[i++])))
			{
				while((drn = readdir(dir)) != NULL)
				{
					if (b++ >= 2)
						ft_putendl(drn->d_name);
				}
				if (closedir(dir) == -1)
					ft_putendl("ERROR WHILE CLOSING DIRECTORY");
			}
			else
				ft_putendl("ERROR WHILE READING FILE");
			b = 0;
		}
	}
	drn = drn;
	return (0);
}
