/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:09:10 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/10 19:23:00 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_instructions(t_vars *vars)
{
	int		y;
	void	*mlx;
	void	*win;

	mlx = vars->mlx;
	win = vars->win;
	y = 0;
	mlx_string_put(mlx, win, 15, y += 15, 0x3A3A3A, "Controls:");
	mlx_string_put(mlx, win, 15, y += 40, 0x3A3A3A, "Move: W, A, S, D, Arrows");
	mlx_string_put(mlx, win, 15, y += 20, 0x3A3A3A, "Zoom: Middle Wheel");
	mlx_string_put(mlx, win, 15, y += 20, 0x3A3A3A, "Flatten: + / -");
	mlx_string_put(mlx, win, 15, y += 30, 0x3A3A3A, "Rotate:");
	mlx_string_put(mlx, win, 15, y += 20, 0x3A3A3A, "  x (+ / -): U / J");
	mlx_string_put(mlx, win, 15, y += 20, 0x3A3A3A, "  y (+ / -): I / K");
	mlx_string_put(mlx, win, 15, y += 20, 0x3A3A3A, "  z (+ / -): O / L");
	mlx_string_put(mlx, win, 15, y += 30, 0x3A3A3A, "Toggle Perspective: P");
	mlx_string_put(mlx, win, 15, y += 20, 0x3A3A3A, "(Isometric and Parallel)");
	mlx_string_put(mlx, win, 15, y += 30, 0x3A3A3A, "Reset: R");
}

void	put_pixel(t_vars *vars, t_point point)
{
	char	*pxl;
	int		x;
	int		y;
	int		color;

	x = point.x;
	y = point.y;
	color = point.color;
	if (x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT)
	{
		pxl = vars->addr + (y * vars->line_len + x * (vars->bpp / 8));
		*(unsigned int *)pxl = color;
	}
}

void	draw_line(t_vars *vars, t_point point1, t_point point2)
{
	float	dx;
	float	dy;
	int		step;
	int		i;
	t_point	point;

	dx = point2.x - point1.x;
	dy = point2.y - point1.y;
	if (fabsf(dx) >= fabsf(dy))
		step = fabsf(dx);
	else
		step = fabsf(dy);
	dx /= step;
	dy /= step;
	i = 0;
	while (i <= step)
	{
		point.x = point1.x + dx * i;
		point.y = point1.y + dy * i;
		point.color = point1.color;
		put_pixel(vars, point);
		i++;
	}
}

void	draw_background(t_vars *vars)
{
	int		height;
	int		width;
	t_point	point;

	height = 0;
	width = 0;
	while (height < HEIGHT)
	{
		width = 0;
		while (width < WIDTH)
		{
			point.x = width;
			point.y = height;
			point.color = 0xFFF1DA;
			put_pixel(vars, point);
			width++;
		}
		height++;
	}
}

void	draw_image(t_vars *vars)
{
	int		i;
	t_point	*points;

	points = malloc(vars->height * vars->width * sizeof (t_point));
	if (!points)
	{
		free_map_tab(vars->tab, vars->height, vars->width);
		exit_handler("Malloc failure.\n");
	}
	map_to_points(*vars, points);
	draw_background(vars);
	i = 0;
	while (i < vars->width * vars->height)
	{
		if ((i + 1) % vars->width)
			draw_line(vars, points[i], points[i + 1]);
		if (i < vars->height * vars->width - vars->width)
			draw_line(vars, points[i], points[i + vars->width]);
		i++;
	}
	free(points);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	write (2, "OK\n", 3);
	draw_instructions(vars);
}
