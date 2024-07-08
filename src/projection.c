/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 15:05:19 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/07 15:41:14 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate_x(int *y, int *z, double angle)
{
	int	yy;

	yy = *y;
	*y = yy * cos(angle) - *z * sin(angle);
	*z = yy * sin(angle) + *z * cos(angle);
}

static void	rotate_y(int *x, int *z, double angle)
{
	int	xx;

	xx = *x;
	*x = xx * cos(angle) + *z * sin(angle);
	*z = *z * cos(angle) - xx * sin(angle);
}

static void	rotate_z(int *x, int *y, double angle)
{
	int	xx;

	xx = *x;
	*x = xx * cos(angle) - *y * sin(angle);
	*y = xx * sin(angle) + *y * cos(angle);
}

t_point
