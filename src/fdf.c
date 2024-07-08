/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:03:25 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/08 17:30:50 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exit_handler(char *s)
{
	ft_putstr_fd(s, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

static void	check_map(int fd)
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

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

int key_press(int keycode, t_vars *vars)
{
	if (keycode == 53)
		mlx_destroy_window(vars->mlx, vars->win);
//	else if (keycode == )

	return(0);
}
/*
int button_press(int button, int x, int y, void *param)
{
	(void)x;
	(void)y;
	(void)param;
	if (button == 1)
		mlx_destroy_window(vars->mlx, vars->win);
	else if (keycode == )

	return(0);
}
*/
/*
typedef struct s_point {
    int x;
    int y;
    int z;
}               t_point;

t_point project_point(int x, int y, int z)
{
    t_point point;

    // Simple isometric projection
    point.x = (x - y) * 10 + WIN_WIDTH / 2;
    point.y = (x + y - z) * 5 + WIN_HEIGHT / 2;
    return point;
}

void draw_line(void *mlx, void *win, t_point p1, t_point p2)
{
    int dx = abs(p2.x - p1.x);
    int dy = abs(p2.y - p1.y);
    int sx = p1.x < p2.x ? 1 : -1;
    int sy = p1.y < p2.y ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (1)
    {
        mlx_pixel_put(mlx, win, p1.x, p1.y, 0xFFFFFF);
        if (p1.x == p2.x && p1.y == p2.y)
            break;
        e2 = err;
        if (e2 > -dx) { err -= dy; p1.x += sx; }
        if (e2 < dy) { err += dx; p1.y += sy; }
    }
}
*/
static void	draw_menu(t_vars var)
{
	int		y;
	void	*mlx;
	void	*win;

	mlx = var.mlx;
	win = var.win;
	y = 0;
	mlx_string_put(mlx, win, 15, y += 15, WHITE, "Controls:");
	mlx_string_put(mlx, win, 15, y += 40, WHITE, "Reset: R");
	mlx_string_put(mlx, win, 15, y += 20, WHITE, "Move: W, A, S, D");
	mlx_string_put(mlx, win, 15, y += 20, WHITE, "Zoom: Arrows");
	mlx_string_put(mlx, win, 15, y += 20, WHITE, "Flatten: + / -");
	mlx_string_put(mlx, win, 15, y += 20, WHITE, "Rotate:");
	mlx_string_put(mlx, win, 15, y += 20, WHITE, "  x (+ / -): U / J");
	mlx_string_put(mlx, win, 15, y += 20, WHITE, "  y (+ / -): I / K");
	mlx_string_put(mlx, win, 15, y += 20, WHITE, "  z (+ / -): O / L");
	mlx_string_put(mlx, win, 15, y += 20, WHITE, "Toggle Perspective: P");
	mlx_string_put(mlx, win, 15, y += 20, WHITE, "(Isometric and Parallel)");
}

int	main(int argc, char **argv)
{
	int	fd;
	//t_data	*data;

	if (argc != 2)
		exit_handler("Usage: $>./fdf /maps/map.fdf\n");
	fd = open_map(argv[1]);
	check_map(fd);

	t_vars vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "FdF");
	/*data = malloc(width * height * sizeof (t_data));
	int i = 0;
	int a = 0;
	int ***tab = fill_tab(fd);
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			data[a]->x = ;
			data[a]->y = ;
			data[a]->z = tab[i][j][0];
		}
	}*/
	draw_menu(vars);
	mlx_hook(vars.win, 2, 1L<<0, key_press, &vars);
	//mlx_hook(vars.win, 4, 1L<<2, , close_window, &vars);
	mlx_loop(vars.mlx);
	close(fd);
}
