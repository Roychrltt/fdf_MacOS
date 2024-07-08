/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:09:10 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/08 19:21:34 by xiaxu            ###   ########.fr       */
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

