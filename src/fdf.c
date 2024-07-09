/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:03:25 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/09 10:41:23 by xiaxu            ###   ########.fr       */
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
		if (s[i] != c && s[i] != '\n' && (s[i + 1] == c || !s[i + 1]))
			count++;
		i++;
	}
	return (count);
}

static void	check_map(char *map)
{
	int		num;
	int		cur;
	int		fd;
	char	*line;

	num = get_width(map);
	fd = open_map(map);
	line = get_next_line(fd);
	if (!line)
		exit_handler("Empty map!\n");
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		cur = count_word(line, ' ');
		if (cur != num)
		{
			free(line);
			exit_handler("Invalid map!\n");
		}
	}
	close(fd);
}

int key_press(int keycode, t_vars *vars)
{
	if (keycode == 53)
		mlx_destroy_window(vars->mlx, vars->win);
	//	else if (keycode == )

	return(0);
}

void	isometric(t_vars *var, int *x, int *y, int z)
{
	int	prev_x;
	int	prev_y;

	if (!var->iso)
		return ;
	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * cos(0.523599);
	*y = -z + (prev_x + prev_y) * sin(0.523599);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_point	*points;
	t_img	img;
	int		i;
	int		j;
	int		a;
	int		fd;
	int		***tab;

	if (argc != 2)
		exit_handler("Usage: $>./fdf /maps/map.fdf\n");
	check_map(argv[1]);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "FdF");
	points = malloc(WIDTH * HEIGHT * sizeof (t_point));
	if (!points)
		exit_handler("Malloc failure.\n");
	i = 0;
	a = 0;
	fd = open_map(argv[1]);
	tab = fill_tab(argv[i], fd);
	close(fd);
	//error free by far, 3d tab created with position and color
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			points[a].x = j;
			points[a].y = i;
			points[a].z = tab[i][j][0];
			j++;
			a++;
		}
		i++;
	}
	i = 0;
	a = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			isometric(&vars, &points[a].x, &points[a].y, points[a].z);
			j++;
			a++;
		}
		i++;
	}
	img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	draw_background(&img);
	i = 0;
	while (i < WIDTH * HEIGHT)
	{
		put_pixel(&img, points[i].x, points[i].y, 0xF3F3F3);
		i++;
	}
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	draw_instructions(vars);
	mlx_hook(vars.win, 2, 1L<<0, key_press, &vars);
	//mlx_hook(vars.win, 4, 1L<<2, , close_window, &vars);
	mlx_loop(vars.mlx);
	free(points);
}
