/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:25:52 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/10 20:31:14 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	update_image(t_vars *vars)
{
	draw_image(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	draw_instructions(vars);
}

static void	close_window(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img);
	mlx_destroy_window(vars->mlx, vars->win);
	free(vars->mlx);
	exit(EXIT_SUCCESS);
}

static void	reset_image(t_vars *vars)
{
	vars->iso = 1;
	vars->flatten = 1;
	vars->angle = 0.523599;
	vars->scale = 10;
	vars->shift_x = WIDTH / 2;
	vars->shift_y = HEIGHT / 4;
}

static void	handle_move(int keycode, t_vars *vars)
{
	if (keycode == KEY_W)
		vars->shift_y += SHIFT;
	if (keycode == KEY_S)
		vars->shift_y -= SHIFT;
	if (keycode == KEY_A)
		vars->shift_x += SHIFT;
	if (keycode == KEY_D)
		vars->shift_x -= SHIFT;
	if (keycode == KEY_PLUS)
		vars->scale++;
	if (keycode == KEY_MINUS)
		vars->scale--;
	if (keycode == KEY_LEFT)
		vars->angle -= 0.1;
	if (keycode == KEY_RIGHT)
		vars->angle += 0.1;
	if (keycode == KEY_UP)
		vars->flatten *= 1.5;
	if (keycode == KEY_DOWN)
		vars->flatten /= 1.5;
	if (keycode == KEY_R)
		reset_image(vars);
	if (keycode == KEY_P)
		vars->iso = 0;
	update_image(vars);
}

int	key_press(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
		close_window(vars);
	else if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_S
		|| keycode == KEY_D)
		handle_move(keycode, vars);
	else if (keycode == KEY_PLUS || keycode == KEY_MINUS)
		handle_move(keycode, vars);
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		handle_move(keycode, vars);
	else if (keycode == KEY_UP || keycode == KEY_DOWN)
		handle_move(keycode, vars);
	else if (keycode == KEY_R || keycode == KEY_P)
		handle_move(keycode, vars);
	return (0);
}
