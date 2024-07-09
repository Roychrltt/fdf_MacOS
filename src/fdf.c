/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:03:25 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/09 21:07:51 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	count_word(char const *s, char c)
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

int key_press(int keycode, t_vars *vars)
{
	if (keycode == 53)
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	//	else if (keycode == )

	return(0);
}

void	isometric(t_vars vars, int *x, int *y, int z)
{
	int	prev_x;
	int	prev_y;

	if (!vars.iso)
		return ;
	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * cos(0.523599);
	*y = -z + (prev_x + prev_y) * sin(0.523599);
}

void	map_to_points(t_vars vars, t_point *points, t_map map)
{
	int		i;
	int		j;
	int		index;

	i = 0;
	index = 0;
	while (i < map.height)
	{
		j = 0;
		while (j < map.width)
		{
			points[index].x = j;
			points[index].y = i;
			points[index].z = map.tab[i][j][0];
			points[index].color = map.tab[i][j][1];
			j++;
			index++;
		}
		i++;
	}
	i = 0;
	index = 0;
	while (i < map.height)
	{
		j = 0;
		while (j < map.width)
		{
			isometric(vars, &points[index].x, &points[index].y, points[index].z);
			j++;
			index++;
		}
		i++;
	}
}

static void	check_init_map(t_map *map)
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

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_point	*points;
	t_img	img;
	t_map	map;

	if (argc != 2)
		exit_handler("Usage: $>./fdf /maps/map.fdf\n");
	map.path = argv[1];
	check_init_map(&map);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "FdF");
	points = malloc(map.height * map.width * sizeof (t_point));
	if (!points)
		exit_handler("Malloc failure.\n");
	map_to_points(vars, points, map);
	img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	draw_image(&img, map, points);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	draw_instructions(vars);
	mlx_hook(vars.win, 2, 1L<<0, key_press, &vars);
	//mlx_hook(vars.win, 4, 1L<<2, , close_window, &vars);
	mlx_loop(vars.mlx);
	free(points);
}
