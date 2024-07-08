/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:03:12 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/08 13:45:11 by xiaxu            ###   ########.fr       */
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

# define WIDTH 1000
# define HEIGHT 680

# define KEY_ESC 53

# define WHITE 0xFFFFFF

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		ppb;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_fdf
{
	void	*mlx;
	void	*win;
	t_img	*img;
	t_point	*point;
	int		max;
	int		min;
	int		zoom;
	int		***map;
}	t_fdf;


int		get_width(char *s, char c);
int		get_height(int fd, char *line);
void	exit_handler(char *s);
void	free_tab_int(int ***tab, int i);
void	free_tab_char(char **tab);
int		***create_matrix(int fd);
int		***fill_tab(int fd);

#endif
