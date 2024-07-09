/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:03:25 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/09 23:32:47 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_press(int keycode, t_vars *vars)
{
	if (keycode == 53)
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
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
			isometric(vars, &points[index].x, &points[index].y, points[index].z);
			j++;
			index++;
		}
		i++;
	}
}

void	init_my_vars(t_vars *vars, t_map *map)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "FdF");
	vars->img = malloc(sizeof (t_img));
	if (!vars->img)
	{
		free_map_tab(map->tab, map->height, map->width);
		exit_handler("Malloc error.\n");
	}
	vars->img->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	vars->img->addr = mlx_get_data_addr(vars->img->img, &vars->img->bpp,
			&vars->img->line_len, &vars->img->endian);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_point	*points;
	t_map	map;

	if (argc != 2)
		exit_handler("Usage: $>./fdf /maps/map.fdf\n");
	map.path = argv[1];
	check_init_map(&map);
	init_my_vars(&vars, &map);
	points = malloc(map.height * map.width * sizeof (t_point));
	if (!points)
		exit_handler("Malloc failure.\n");
	map_to_points(vars, points, map);
	draw_image(&vars, map, points);
	mlx_hook(vars.win, 2, 1L<<0, key_press, &vars);
	//mlx_hook(vars.win, 4, 1L<<2, , close_window, &vars);
	mlx_loop(vars.mlx);
	free(points);
	free_map_tab(map.tab, map.height, map.width);
}
