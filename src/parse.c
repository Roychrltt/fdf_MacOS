/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:57:40 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/08 17:36:38 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_width(char *map)
{
	size_t	i;
	int		width;
	char	*s;
	int		fd;

	i = 0;
	fd = open_map(map);
	s = get_next_line(fd);
	width = 0;
	while (s[i])
	{
		if (s[i] != ' ' && (s[i + 1] == ' ' || !s[i + 1]))
			width++;
		i++;
	}
	close(fd);
	return (width);
}

int	get_height(char *map)
{
	int		height;
	int		fd;
	char	*line;

	fd = open_map(map);
	line = get_next_line(fd);
	height = 1;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		height++;
	}
	return (height);
}

void	check_map(int fd)
{
	int		num;
	int		cur;
	char	*line;

	line = get_next_line(fd);
	if (!line)
		exit_handler("Empty map!\n");
	num = get_width(line, ' ');
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		cur = get_width(line, ' ');
		if (cur != num)
		{
			free(line);
			exit_handler("Invalid map!\n");
		}
	}
}

int	***create_matrix(int fd)
{
	int		height;
	int		width;
	char	*line;
	int		***tab;
	int		i;

	line = get_next_line(fd);
	width = get_width(line, ' ');
	height = get_height(fd, line);
	tab = malloc(height * sizeof (int **));
	if (!tab)
		exit_handler("Malloc failure.\n");
	i = 0;
	while (i < height)
	{
		tab[i] = malloc(width * sizeof (int[2]));
		if (!tab[i])
		{
			free_tab_int(tab, i);
			exit_handler("Malloc failure.\n");
		}
		i++;
	}
	return (tab);
}

int	***fill_tab(int fd)
{
	int		***tab;
	int		i;
	int		j;
	char	*line;
	char	**nums;

	tab = create_matrix(fd);
	i = 0;
	while (tab[i])
	{
		line = get_next_line(fd);
		nums = ft_split(line, ' ');
		j = 0;
		while (tab[i][j])
		{
			tab[i][j][0] = ft_atoi(nums[j]);
			j++;
		}
		free(line);
		free_tab_char(nums);
		i++;
	}
	return (tab);
}
