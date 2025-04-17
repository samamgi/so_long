/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_rectangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 02:49:32 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/04/17 02:49:33 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	set_rectangle_util(t_data *data, int fd)
{
	int	i;

	while (1)
	{
		i = -1;
		data->line = get_next_line(fd);
		if (!data->line)
		{
			close(fd);
			break ;
		}
		if (data->line[0] == '\n' || data->line[0] == '\0')
		{
			free(data->line);
			data->line = NULL;
			return (close(fd), -1);
		}
		data->longueur = 0;
		while (data->line[++i] && data->line[i] != '\n')
			data->longueur += 64;
		free(data->line);
		data->hauteur += 64;
	}
	return (1);
}

int	set_rectangle(t_data *data, char **av)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error: ", 2);
		perror(av[1]);
		return (-9);
	}
	if (set_rectangle_util(data, fd) != 1)
		return (-1);
	if (data->hauteur == data->longueur)
		return (-4);
	else
	{
		data->lines = (data->hauteur / 64);
		return (1);
	}
}
