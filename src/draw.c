/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:09:10 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/09 14:20:54 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_instructions(t_vars var)
{
	int		y;
	void	*mlx;
	void	*win;

	mlx = var.mlx;
	win = var.win;
	y = 0;
	mlx_string_put(mlx, win, 15, y += 15, WHITE, "Controls:");
	mlx_string_put(mlx, win, 15, y += 40, WHITE, "Move: W, A, S, D, Arrows");
	mlx_string_put(mlx, win, 15, y += 20, WHITE, "Zoom: Middle Wheel");
	mlx_string_put(mlx, win, 15, y += 20, WHITE, "Flatten: + / -");
	mlx_string_put(mlx, win, 15, y += 30, WHITE, "Rotate:");
	mlx_string_put(mlx, win, 15, y += 20, WHITE, "  x (+ / -): U / J");
	mlx_string_put(mlx, win, 15, y += 20, WHITE, "  y (+ / -): I / K");
	mlx_string_put(mlx, win, 15, y += 20, WHITE, "  z (+ / -): O / L");
	mlx_string_put(mlx, win, 15, y += 30, WHITE, "Toggle Perspective: P");
	mlx_string_put(mlx, win, 15, y += 20, WHITE, "(Isometric and Parallel)");
	mlx_string_put(mlx, win, 15, y += 30, WHITE, "Reset: R");
}

void	put_pixel(t_img *img, t_point point)
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
		pxl = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *)pxl = color;
	}
}
/*
void	draw_line(t_map *map, t_point point0, t_point point1)
{
	float	step;
	float	x;
	float	y;
	int		i;
	t_delta	delta;

	i = 0;
	delta.dx = point1.x - point0.x;
	delta.dy = point1.y - point0.y;
	if (abs(delta.dx) >= abs(delta.dy))
		step = fabsf(delta.dx);
	else
		step = fabsf(delta.dy);
	delta.dx = delta.dx / step;
	delta.dy = delta.dy / step;
	x = point0.x;
	y = point0.y;
	while (i < step)
	{
		put_pixel(env, -x + WINDOW_WIDTH / 2 + env->translation, \
				-y + HEIGHT / 2 + env->translation, 0xFFFFFF);
		x = x + delta.dx;
		y = y + delta.dy;
		i++;
	}
}
*/
void	draw_background(t_img *img)
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
			point.color = 0x1b1b1b;
			put_pixel(img, point);
			width++;
		}
		height++;
	}
}

void	draw_image(t_img *img, t_map map, t_point *points)
{
	int	i;

	i = 0;
	draw_background(img);
	while (i < map.width * map.height)
		put_pixel(img, points[i++]);
}
