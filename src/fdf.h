/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:03:12 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/10 19:28:25 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

# define WIDTH 1200
# define HEIGHT 700
# define SHIFT 10

# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	int		iso;
	float	flatten;
	float	angle;
	int		scale;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	char	*path;
	int		fd;
	int		height;
	int		width;
	int		***tab;
	int		shift_x;
	int		shift_y;
}	t_vars;

// parse
void	get_map_size(t_vars *vars);
void	create_matrix(t_vars *vars);
void	fill_tab(t_vars *vars);
void	check_init_map(t_vars *vars);
void	isometric(t_vars vars, int *x, int *y, int z);
void	map_to_points(t_vars vars, t_point *points);

// draw
void	put_pixel(t_vars *vars, t_point point);
void	draw_line(t_vars *vars, t_point point1, t_point point2);
void	draw_instructions(t_vars *vars);
void	draw_background(t_vars *vars);
void	draw_image(t_vars *vars);

// event
int		key_press(int keycode, t_vars *vars);

// free
void	free_tab_int(int ***tab, int i);
void	free_tab_int2(int ***tab, int i, int j, int w);
void	free_map_tab(int ***tab, int h, int w);
void	free_tab_char(char **tab);
void	handle_split_failure(char *s, t_vars *vars, int i);

// utils
void	exit_handler(char *s);
int		open_map(char *map);
int		count_word(char const *s, char c);

#endif
