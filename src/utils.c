/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:28:48 by xiaxu             #+#    #+#             */
/*   Updated: 2024/10/23 12:55:37 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exit_handler(char *s)
{
	ft_putstr_fd(s, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int	open_map(char *map)
{
	int	fd;

	fd = open(map, O_RDONLY);
	if (fd == -1)
	{
		perror("Map open failure");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	count_word(char const *s, char c)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && s[i] != '\n'
			&& (s[i + 1] == c || !s[i + 1] || s[i + 1] == '\n'))
			count++;
		i++;
	}
	return (count);
}
/*
void	isometric(t_vars->vars-> int *x, int *y, int z)
{
	int	prev_x;
	int	prev_y;

	prev_x = *x;
	prev_y = *y;
	if (!vars->iso)
	{
		*x = prev_x * vars->scale;
		*y = prev_y * vars->scale; 
	}
	else
	{
		*x = ((prev_x - prev_y) * cos(vars->angle)) * vars->scale;
		*y = (-z * vars->flatten + (prev_x + prev_y) * sin(vars->angle)) * vars->scale;
	}
	prev_x = *x - WIDTH / 2;
	prev_y = *y - HEIGHT / 2;
	*x = prev_x * cos(vars->swirl) - prev_y * sin(vars->swirl) + WIDTH / 2 + vars->shift_x;
	*y = prev_x * sin(vars->swirl) + prev_y * cos(vars->swirl) + HEIGHT / 2 + vars->shift_y;
}
*/

void	isometric(t_vars *vars, int *x, int *y, int z)
{
	int	prev_x;
	int	prev_y;

//	*x -= WIDTH / 2;
//	*y -= HEIGHT / 2;
	prev_x = *x;
	prev_y = *y;
	*x = ((prev_x - prev_y) * cos(vars->angle));
	*y = (-z * vars->flatten + (prev_x + prev_y) * sin(vars->angle));
	prev_x = *x - vars->shift_x + WIDTH / 2;
	prev_y = *y - vars->shift_y + HEIGHT / 2;
	*x = prev_x * cos(vars->swirl) - prev_y * sin(vars->swirl); 
	*y = prev_x * sin(vars->swirl) + prev_y * cos(vars->swirl);
	//	*x += vars->shift_x + WIDTH / 2;
	//	*y += vars->shift_y + HEIGHT / 2;
	*x += vars->shift_x;
	*y += vars->shift_y;
}

void	map_to_points(t_vars *vars, t_point *points)
{
	int		i;
	int		j;
	int		index;

	i = 0;
	index = 0;
	while (i < vars->height)
	{
		j = 0;
		while (j < vars->width)
		{
			points[index].x = j;
			points[index].y = i;
			points[index].z = vars->tab[i][j][0];
			points[index].color = vars->tab[i][j][1];
			isometric(vars, &points[index].x, &points[index].y,
					points[index].z);
			j++;
			index++;
		}
		i++;
	}
	vars->key = 0;
}
