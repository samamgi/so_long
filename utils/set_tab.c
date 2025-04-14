/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 02:49:38 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/04/17 02:49:39 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	set_tab_util_2(t_data *data, int j, int i, int fd)
{
	while (data->line[i] && data->line[i] != '\n')
	{
		if (put_img(data, data->line, i, j) == -1)
		{
			close(fd);
			return (-1);
		}
		(data->tab)[j][i] = data->line[i];
		i++;
		data->longueur += 64;
	}
	return (1);
}

int	set_tab_util(t_data *data, int j, int i, int fd)
{
	while (1)
	{
		i = -1;
		data->line = get_next_line(fd);
		if (!data->line)
			break ;
		if (data->line[0] == '\n' || data->line[0] == '\0')
			return (free(data->line), data->line = NULL, close(fd), -1);
		data->tab[j] = malloc(sizeof(char) * (ft_strlen(data->line) + 1));
		if (!data->tab[j])
			return (free(data->line), data->line = NULL, close(fd), -8);
		while (data->line[++i] && data->line[i] != '\n')
		{
			if (put_img(data, data->line, i, j) == -1)
				return (free(data->line), data->line = NULL, close(fd), -1);
			data->tab[j][i] = data->line[i];
			data->longueur += 64;
		}
		data->tab[j][i] = 0;
		free(data->line);
		data->longueur = 0;
		data->hauteur += 64;
		j++;
	}
	return (close(fd), 1);
}

int	set_tab(t_data *data, char **av)
{
	int	fd;
	int	i;
	int	j;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (-9);
	data->tab = (char **)malloc(sizeof(char *) * ((data->lines) + 1));
	if (!data->tab)
		return (0);
	(data->tab)[data->lines] = 0;
	i = 0;
	while (i < data->lines)
	{
		data->tab[i] = NULL;
		i++;
	}
	j = 0;
	data->collect = 0;
	data->p = 0;
	data->e = 0;
	data->hauteur = 0;
	data->longueur = 0;
	return (set_tab_util(data, j, i, fd));
}
