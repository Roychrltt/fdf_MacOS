/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:54:56 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/09 23:06:43 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_tab_int(int ***tab, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	exit_handler("Malloc failure.\n");
}

void	free_tab_int2(int ***tab, int i, int j, int w)
{
	int	a;
	int	b;

	a = 0;
	while (a < j)
		free(tab[i][a++]);
	free(tab[i]);
	a = 0;
	while (a < i)
	{
		b = 0;
		while (b < w)
			free(tab[a][b++]);
		free(tab[a++]);
	}
	free(tab);
	exit_handler("Malloc failure.\n");
}

void	free_map_tab(int ***tab, int h, int w)
{
	int	i;
	int	j;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			free(tab[i][j]);
			j++;
		}
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_tab_char(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	handle_split_failure(char *s, t_map *map, int i)
{
	free(s);
	free_tab_int(map->tab, i);
	close(map->fd);
	exit_handler("Malloc failure.\n");
}
