/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 02:48:54 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/04/17 02:48:57 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	close_window(t_data *data)
{
	free_data(data);
	return (0);
}

int	init_data(t_data *data, int longueur, int hauteur)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, longueur, hauteur, "so_long");
	data->dirt.img_dirt = mlx_xpm_file_to_image(data->mlx, "img/dirt.xpm",
			&(data->dirt.img_w_dirt), &(data->dirt.img_h_dirt));
	data->diamond.img_diamond = mlx_xpm_file_to_image(data->mlx,
			"img/diamond.xpm", &(data->diamond.img_w_diamond),
			&(data->diamond.img_h_diamond));
	data->bedrock.img_bedrock = mlx_xpm_file_to_image(data->mlx,
			"img/bedrock.xpm", &(data->bedrock.img_w_bedrock),
			&(data->bedrock.img_h_bedrock));
	data->steve.img_steve = mlx_xpm_file_to_image(data->mlx, "img/steve.xpm",
			&(data->steve.img_w_steve), &(data->steve.img_h_steve));
	data->portal.img_portal = mlx_xpm_file_to_image(data->mlx,
			"img/portal.xpm", &(data->portal.img_w_portal),
			&(data->portal.img_h_portal));
	if (!data->steve.img_steve || !data->dirt.img_dirt
		|| !data->diamond.img_diamond || !data->bedrock.img_bedrock
		|| !data->portal.img_portal)
		return (-7);
	return (1);
}

int	put_img(t_data *data, char *line, int i, int j)
{
	if (line[i] == '1')
		put_bedrock(data);
	else if (line[i] == '0')
		put_dirt(data);
	else if (line[i] == 'C')
		put_diamond(data);
	else if (line[i] == 'P')
		put_steve(data, i, j);
	else if (line[i] == 'E')
		put_portal(data);
	else
		return (-1);
	return (1);
}

void	initmlx(char **av)
{
	t_data	data;

	init_data_0(&data);
	if (put_error(set_rectangle(&data, av)) <= 0 || put_error(init_data(&data,
				data.longueur, data.hauteur)) <= 0 || put_error(set_tab(&data,
				av)) <= 0 || put_error(check_map(data.tab, &data, ((data.lines)
					- 1))) <= 0 || put_error(check_finding(&data)) <= 0)
	{
		free_data(&data);
		return ;
	}
	mlx_hook(data.win, 2, 1L << 0, move, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_loop(data.mlx);
	free_data(&data);
}

int	check_ber(char **av)
{
	int	i;
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error: ", 2);
		perror(av[1]);
		return (-1);
	}
	i = (ft_strlen(av[1]) - 1);
	if (av[1][i] != 'r' || av[1][i - 1] != 'e' || av[1][i - 2] != 'b' || av[1][i
		- 3] != '.')
	{
		close(fd);
		ft_putendl_fd("Error: Map Extension", 2);
		return (-1);
	}
	close(fd);
	return (1);
}
