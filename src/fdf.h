/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:03:12 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/09 21:07:25 by xiaxu            ###   ########.fr       */
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

# define KEY_ESC 53

# define WHITE 0xFFFFFF

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_map
{
	char	*path;
	int		fd;
	int		height;
	int		width;
	int		***tab;
}				t_map;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	int		iso;
}	t_vars;

// parse
void	get_map_size(t_map *map);
int		***create_matrix(t_map *map);
int		***fill_tab(t_map *map);

// draw
void	put_pixel(t_img *img, t_point point);
void	draw_line(t_map *map, t_point point0, t_point point1);
void	draw_instructions(t_vars var);
void	draw_background(t_img *img);
void	draw_image(t_img *img, t_map map, t_point *points);

// free
void	free_tab_int(int ***tab, int i);
void	free_tab_char(char **tab);

// utils
void	exit_handler(char *s);
int		open_map(char *map);

#endif
