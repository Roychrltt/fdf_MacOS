/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:57:40 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/09 22:59:24 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_map_size(t_map *map)
{
	size_t	i;
	int		fd;
	char	*s;

	i = 0;
	fd = open_map(map->path);
	s = get_next_line(fd);
	map->width = 0;
	if (!s)
		return ;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\n'
			&& (!s[i + 1] || s[i + 1] == '\n' || s[i + 1] == ' '))
			map->width++;
		i++;
	}
	map->height = 0;
	while (s)
	{
		map->height++;
		free(s);
		s = get_next_line(fd);
	}
	close(fd);
}

void	create_matrix(t_map *map)
{
	int		i;
	int		j;

	map->tab = malloc(map->height * sizeof (int **));
	if (!map->tab)
		exit_handler("Malloc failure.\n");
	i = 0;
	while (i < map->height)
	{
		map->tab[i] = malloc(map->width * sizeof (int *));
		if (!map->tab[i])
			free_tab_int(map->tab, i);
		j = 0;
		while (j < map->width)
		{
			map->tab[i][j] = malloc(2 * sizeof (int ));
			if (!tab[i][j])
				free_tab_int2(tab, i, j, map->width);
			j++;
		}
		i++;
	}
}

static unsigned int	get_color(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != ',')
		i++;
	if (!s[i])
		return (0xF3F3F3);
	else
		return (ft_atoi_base(s + i + 1, "0123456789ABCDEF"));
}

int	***fill_tab(t_map *map)
{
	int		i;
	int		j;
	char	*line;
	char	**nums;

	create_matrix(map);
	i = 0;
	while (i < map->height)
	{
		line = get_next_line(map->fd);
		nums = ft_split(line, ' ');
		if (!nums)
			handle_split_failure(line, map, i);
		j = 0;
		while (nums[j + 1])
		{
			map->tab[i][j][0] = ft_atoi(nums[j]);
			map->tab[i][j][1] = get_color(nums[j]);
			j++;
		}
		free(line);
		free_tab_char(nums);
		i++;
	}
	return (map->tab);
}

void	check_init_map(t_map *map)
{
	int		cur;
	char	*line;

	get_map_size(map);
	map->fd = open_map(map->path);
	line = get_next_line(map->fd);
	if (!line)
		exit_handler("Empty map!\n");
	while (line)
	{
		free(line);
		line = get_next_line(map->fd);
		if (!line)
			break ;
		cur = count_word(line, ' ');
		if (cur != map->width)
		{
			free(line);
			exit_handler("Invalid map!\n");
		}
	}
	close(map->fd);
	map->fd = open_map(map->path);
	map->tab = fill_tab(map);
	close(map->fd);
}
