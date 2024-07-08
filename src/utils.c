/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:28:48 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/08 18:46:08 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exit_handler(char *s)
{
	ft_putstr_fd(s, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int	open_map(char *map)
{
	int	fd;

	fd = open(map, O_RDONLY);
	if (fd == -1)
	{
		perror("Map open failure");
		exit(EXIT_FAILURE);
	}
	return (fd);
}
