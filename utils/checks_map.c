/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 02:49:14 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/04/17 02:49:15 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	check_map(char **tab, t_data *data, int y_max)
{
	int	i;

	i = 0;
	if ((ft_strchr(tab[0], '1') == 1) || (ft_strchr(tab[y_max], '1') == 1))
		return (-5);
	if ((data->p) > 1 || (data->p) == 0 || (data->e) > 1 || (data->e) == 0
		|| data->collect < 1)
	{
		if ((data->p) > 1 || (data->e) > 1)
			return (-2);
		return (-3);
	}
	while (tab[i + 1])
	{
		if (ft_strlen(tab[i]) != ft_strlen(tab[i + 1]))
			return (-4);
		i++;
	}
	i = -1;
	while (tab[++i])
	{
		if (tab[i][0] != '1' || tab[i][ft_strlen(tab[i]) - 1] != '1')
			return (-5);
	}
	return (1);
}

char	**copy_tab(char **data_map, int lines)
{
	int		i;
	int		j;
	char	**map;

	j = 0;
	map = (char **)malloc(sizeof(char *) * (lines + 1));
	if (!map)
	{
		free(map);
		return (NULL);
	}
	map[lines] = 0;
	while (data_map[j])
	{
		i = 0;
		map[j] = (char *)malloc(sizeof(char) * (ft_strlen(data_map[j]) + 1));
		while (data_map[j][i])
		{
			map[j][i] = data_map[j][i];
			i++;
		}
		map[j][i] = 0;
		j++;
	}
	return (map);
}

void	flood_fill(char **map, int y, int x)
{
	if (map[y][x] == '1' || map[y][x] == 'X')
		return ;
	if (map[y][x] == '0' || map[y][x] == 'C' || map[y][x] == 'E'
		|| map[y][x] == 'P')
	{
		map[y][x] = 'X';
		flood_fill(map, y + 1, x);
		flood_fill(map, y - 1, x);
		flood_fill(map, y, x + 1);
		flood_fill(map, y, x - 1);
	}
}

int	check_finding_util(char **copy, int y, int x)
{
	while (copy[y])
	{
		x = 0;
		while (copy[y][x])
		{
			if (copy[y][x] == 'C' || copy[y][x] == 'E')
			{
				free_tab(copy);
				return (-6);
			}
			x++;
		}
		y++;
	}
	free_tab(copy);
	return (1);
}

int	check_finding(t_data *data)
{
	char	**copy;
	int		x;
	int		y;

	copy = copy_tab(data->tab, data->lines);
	if (!copy)
	{
		free(copy);
		return (0);
	}
	x = data->player.x;
	y = data->player.y;
	flood_fill(copy, y, x);
	x = 0;
	y = 0;
	return (check_finding_util(copy, y, x));
}
