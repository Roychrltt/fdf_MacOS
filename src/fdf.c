/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:03:25 by xiaxu             #+#    #+#             */
/*   Updated: 2024/10/23 10:24:28 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_my_vars(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "FdF");
	vars->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bpp, &vars->line_len,
			&vars->endian);
	vars->iso = 1;
	vars->flatten = 1;
	vars->angle = 0.523599;
	vars->swirl = 0.0;
	vars->scale = 10;
	vars->shift_x = WIDTH / 2;
	vars->shift_y = HEIGHT / 2;
	vars->key = 0;
}

static void	check_is_fdf(char *path)
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	if (ft_strncmp(path + i - 4, ".fdf", 5) != 0)
		exit_handler("Wrong map type!\n");
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 2)
		exit_handler("Usage: $>./fdf /maps/map.fdf\n");
	vars.path = argv[1];
	check_is_fdf(argv[1]);
	check_init_map(&vars);
	init_my_vars(&vars);
	mlx_hook(vars.win, 2, 1L << 0, key_press, &vars);
	mlx_hook(vars.win, 17, 1L << 17, close_window, &vars);
	draw_image(&vars);
	mlx_loop(vars.mlx);
	free_map_tab(vars.tab, vars.height, vars.width);
}
