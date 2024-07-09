/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:57:40 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/09 10:33:53 by xiaxu            ###   ########.fr       */
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
	if (!s)
		return (width);
	while (s[i])
	{
		if (s[i] != ' '  && s[i] != '\n' && (s[i + 1] == ' ' || !s[i + 1]))
			width++;
		i++;
	}
	while (s)
	{
		free(s);
		s = get_next_line(fd);
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
	close(fd);
	return (height);
}

int	***create_matrix(char *map)
{
	int		height;
	int		width;
	int		***tab;
	int		i;

	height = get_height(map);
	width = get_width(map);
	tab = malloc(height * sizeof (int **));
	if (!tab)
		exit_handler("Malloc failure.\n");
	i = 0;
	while (i < height)
	{
		tab[i] = malloc(width * sizeof (int [2]));
		if (!tab[i])
		{
			free_tab_int(tab, i);
			exit_handler("Malloc failure.\n");
		}
		i++;
	}
	return (tab);
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

int	***fill_tab(char *map, int fd)
{
	int		***tab;
	int		i;
	int		j;
	char	*line;
	char	**nums;

	tab = create_matrix(map);
	i = 0;
	while (tab[i])
	{
		line = get_next_line(fd);
		nums = ft_split(line, ' ');
		j = 0;
		while (tab[i][j])
		{
			tab[i][j][0] = ft_atoi(nums[j]);
			tab[i][j][1] = get_color(nums[j]);
			j++;
		}
		free(line);
		free_tab_char(nums);
		i++;
	}
	return (tab);
}
