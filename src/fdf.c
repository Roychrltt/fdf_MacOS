/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:03:25 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/10 18:42:52 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric(t_vars vars, int *x, int *y, int z)
{
	int	prev_x;
	int	prev_y;

	if (!vars.iso)
		return ;
	prev_x = *x;
	prev_y = *y;
	*x = ((prev_x - prev_y) * cos(vars.angle)) * vars.scale + WIDTH / 2;
	*y = (-z * vars.flatten + (prev_x + prev_y) * sin(vars.angle))
		* vars.scale + HEIGHT / 4;
}

void	map_to_points(t_vars vars, t_point *points)
{
	int		i;
	int		j;
	int		index;

	i = 0;
	index = 0;
	while (i < vars.height)
	{
		j = 0;
		while (j < vars.width)
		{
			points[index].x = j;
			points[index].y = i;
			points[index].z = vars.tab[i][j][0];
			points[index].color = vars.tab[i][j][1];
			isometric(vars, &points[index].x, &points[index].y,
				points[index].z);
			j++;
			index++;
		}
		i++;
	}
}

void	init_my_vars(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "FdF");
	vars->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bpp, &vars->line_len,
			&vars->endian);
	vars->iso = 1;
	vars->flatten = 0.25;
	vars->angle = 0.523599;
	vars->scale = 10;
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 2)
		exit_handler("Usage: $>./fdf /maps/map.fdf\n");
	vars.path = argv[1];
	check_init_map(&vars);
	init_my_vars(&vars);
	draw_image(&vars);
	mlx_hook(vars.win, 2, 1L << 0, key_press, &vars);
	mlx_hook(vars.win, 17, 1L << 17, key_press, &vars);
	mlx_loop(vars.mlx);
	free_map_tab(vars.tab, vars.height, vars.width);
}
/*
for (int i = 0; i < vars.height; i++)
	{
		for (int j = 0; j < vars.width; j++)
		{
			printf("%d, %u/ ", vars.tab[i][j][0], vars.tab[i][j][1]);
		}
		printf("\n");
	}
*/
