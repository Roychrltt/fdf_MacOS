/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:57:40 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/10 12:54:23 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_map_size(t_vars *vars)
{
	size_t	i;
	int		fd;
	char	*s;

	i = 0;
	fd = open_map(vars->path);
	s = get_next_line(fd);
	vars->width = 0;
	if (!s)
		return ;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\n'
			&& (!s[i + 1] || s[i + 1] == '\n' || s[i + 1] == ' '))
			vars->width++;
		i++;
	}
	vars->height = 0;
	while (s)
	{
		vars->height++;
		free(s);
		s = get_next_line(fd);
	}
	close(fd);
}

void	create_matrix(t_vars *vars)
{
	int		i;
	int		j;

	vars->tab = malloc(vars->height * sizeof (int **));
	if (!vars->tab)
		exit_handler("Malloc failure.\n");
	i = 0;
	while (i < vars->height)
	{
		vars->tab[i] = malloc(vars->width * sizeof (int *));
		if (!vars->tab[i])
			free_tab_int(vars->tab, i);
		j = 0;
		while (j < vars->width)
		{
			vars->tab[i][j] = malloc(2 * sizeof (int ));
			if (!vars->tab[i][j])
				free_tab_int2(vars->tab, i, j, vars->width);
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
		return (0x484848);
	else
		return (ft_atoi_base(s + i + 1, "0123456789ABCDEF"));
}

void	fill_tab(t_vars *vars)
{
	int		i;
	int		j;
	char	*line;
	char	**nums;

	create_matrix(vars);
	i = -1;
	while (++i < vars->height)
	{
		line = get_next_line(vars->fd);
		nums = ft_split(line, ' ');
		if (!nums)
			handle_split_failure(line, vars, i);
		j = -1;
		while (nums[++j])
		{
			if (nums[j][0] == '\n')
				break ;
			vars->tab[i][j][0] = ft_atoi(nums[j]);
			vars->tab[i][j][1] = get_color(nums[j]);
		}
		free(line);
		free_tab_char(nums);
	}
}

void	check_init_map(t_vars *vars)
{
	int		cur;
	char	*line;

	get_map_size(vars);
	vars->fd = open_map(vars->path);
	line = get_next_line(vars->fd);
	if (!line)
		exit_handler("Empty map!\n");
	while (line)
	{
		free(line);
		line = get_next_line(vars->fd);
		if (!line)
			break ;
		cur = count_word(line, ' ');
		if (cur != vars->width)
		{
			free(line);
			exit_handler("Invalid map!\n");
		}
	}
	close(vars->fd);
	vars->fd = open_map(vars->path);
	fill_tab(vars);
	close(vars->fd);
}
