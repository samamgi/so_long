/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:06:02 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/04/16 07:24:39 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "libft/libft.h"
#include "so_long.h"
#include <X11/keysym.h>

int	printmap(char **av)
{
	char	*line;
	int		fd;

	fd = open(av[1], O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		ft_putstr_fd(line, 1);
		if (!line)
			break ;
		free(line);
	}
	close(fd);
	return (fd);
}

typedef struct s_player
{
	int				x;
	int				y;
}					t_player;

typedef struct s_img_dirt
{
	void			*img_dirt;
	int				img_w_dirt;
	int				img_h_dirt;
}					t_img_dirt;

typedef struct s_img_diamond
{
	void			*img_diamond;
	int				img_w_diamond;
	int				img_h_diamond;
}					t_img_diamond;

typedef struct s_img_bedrock
{
	void			*img_bedrock;
	int				img_w_bedrock;
	int				img_h_bedrock;
}					t_img_bedrock;

typedef struct s_img_steve
{
	void			*img_steve;
	int				img_w_steve;
	int				img_h_steve;
}					t_img_steve;

typedef struct s_img_portal
{
	void			*img_portal;
	int				img_w_portal;
	int				img_h_portal;
}					t_img_portal;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	t_img_dirt		dirt;
	t_img_diamond	diamond;
	t_img_bedrock	bedrock;
	t_img_steve		steve;
	t_img_portal	portal;
	t_player		player;
	char			**tab;
	char			*line;
	int				collect;
	int				P;
	int				E;
	int				lines;
	int				longueur;
	int				hauteur;
}					t_data;

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int    free_data(t_data *data)
{
        mlx_clear_window(data->mlx, data->win);
        mlx_destroy_window(data->mlx, data->win);
        if (data->dirt.img_dirt)
                mlx_destroy_image(data->mlx, data->dirt.img_dirt);
        if (data->diamond.img_diamond)
                mlx_destroy_image(data->mlx, data->diamond.img_diamond);
        if (data->bedrock.img_bedrock)
                mlx_destroy_image(data->mlx, data->bedrock.img_bedrock);
        if (data->steve.img_steve)
                mlx_destroy_image(data->mlx, data->steve.img_steve);
        if (data->portal.img_portal)
                mlx_destroy_image(data->mlx, data->portal.img_portal);
        mlx_destroy_display(data->mlx);
        mlx_loop_end(data->mlx);
        if (data->tab)
                free_tab(data->tab);
        if (data->line)
                free(data->line);
        free(data->mlx);
        return (exit(1), 1);
}

int     close_window(t_data *data)
{
        free(data);
        exit(1);
	free(data);
        return (1);
}

int	init_data(t_data *data, int longueur, int hauteur)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, longueur, hauteur, "so_long");
	mlx_hook(data->win, 17, 0, close_window, NULL);
	data->dirt.img_dirt = mlx_xpm_file_to_image(data->mlx, "dirt.xpm",
			&(data->dirt.img_w_dirt), &(data->dirt.img_h_dirt));
	data->diamond.img_diamond = mlx_xpm_file_to_image(data->mlx, "diamond.xpm",
			&(data->diamond.img_w_diamond), &(data->diamond.img_h_diamond));
	data->bedrock.img_bedrock = mlx_xpm_file_to_image(data->mlx, "bedrock.xpm",
			&(data->bedrock.img_w_bedrock), &(data->bedrock.img_h_bedrock));
	data->steve.img_steve = mlx_xpm_file_to_image(data->mlx, "steve.xpm",
			&(data->steve.img_w_steve), &(data->steve.img_h_steve));
	data->portal.img_portal = mlx_xpm_file_to_image(data->mlx, "portal.xpm",
			&(data->portal.img_w_portal), &(data->portal.img_h_portal));
	if (!data->steve.img_steve || !data->dirt.img_dirt
		|| !data->diamond.img_diamond || !data->bedrock.img_bedrock
		|| !data->portal.img_portal)
		return (-7);
	return (1);
}

void	move_right(t_data *data)
{
	if ((data->tab)[data->player.y][(data->player.x) + 1] == '1')
		return;
	if ((data->tab)[data->player.y][(data->player.x)] == 'E')
		mlx_put_image_to_window(data->mlx, data->win, data->portal.img_portal,
			((data->player.x) * 64), ((data->player.y) * 64));
	else
	{
		mlx_put_image_to_window(data->mlx, data->win, data->dirt.img_dirt,
			((data->player.x) * 64), ((data->player.y) * 64));
	}
	(data->player.x) += 1;
	mlx_put_image_to_window(data->mlx, data->win, data->steve.img_steve,
		((data->player.x) * 64), ((data->player.y) * 64));
	return;
}

void	move_down(t_data *data)
{
	if ((data->tab)[(data->player.y) + 1][data->player.x] == '1')
		return;
	if ((data->tab)[data->player.y][(data->player.x)] == 'E')
		mlx_put_image_to_window(data->mlx, data->win, data->portal.img_portal,
			((data->player.x) * 64), ((data->player.y) * 64));
	else
	{
		mlx_put_image_to_window(data->mlx, data->win, data->dirt.img_dirt,
			((data->player.x) * 64), ((data->player.y) * 64));
	}
	(data->player.y) += 1;
	mlx_put_image_to_window(data->mlx, data->win, data->steve.img_steve,
		((data->player.x) * 64), ((data->player.y) * 64));
	return;
}

void	move_up(t_data *data)
{
	if ((data->tab)[(data->player.y) - 1][data->player.x] == '1')
		return;
	if ((data->tab)[data->player.y][(data->player.x)] == 'E')
		mlx_put_image_to_window(data->mlx, data->win, data->portal.img_portal,
			((data->player.x) * 64), ((data->player.y) * 64));
	else
	{
		mlx_put_image_to_window(data->mlx, data->win, data->dirt.img_dirt,
			((data->player.x) * 64), ((data->player.y) * 64));
	}
	(data->player.y) -= 1;
	mlx_put_image_to_window(data->mlx, data->win, data->steve.img_steve,
		((data->player.x) * 64), ((data->player.y) * 64));
	return;
}

void	move_left(t_data *data)
{
	if ((data->tab)[data->player.y][(data->player.x) - 1] == '1')
		return;
	if ((data->tab)[data->player.y][(data->player.x)] == 'E')
		mlx_put_image_to_window(data->mlx, data->win, data->portal.img_portal,
			((data->player.x) * 64), ((data->player.y) * 64));
	else
	{
		mlx_put_image_to_window(data->mlx, data->win, data->dirt.img_dirt,
			((data->player.x) * 64), ((data->player.y) * 64));
	}
	(data->player.x) -= 1;
	mlx_put_image_to_window(data->mlx, data->win, data->steve.img_steve,
		((data->player.x) * 64), ((data->player.y) * 64));
	return;
}

int	move(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		return(free_data(data));
	}
	if (keycode == 'd')
		move_right(data);
	if (keycode == 's')
		move_down(data);
	if (keycode == 'w')
		move_up(data);
	if (keycode == 'a')
		move_left(data);
	if ((data->tab)[data->player.y][data->player.x] == 'C')
	{
		(data->tab)[data->player.y][data->player.x] = '0';
		data->collect -= 1;
	}
	if (((data->tab)[data->player.y][data->player.x] == 'E')
		&& ((data->collect) == 0))
	{
		return (free_data(data));
	}
	return (0);
}

void	print_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putstr_fd(str[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

int	put_error(int code)
{
	if (code == -8)
		ft_putendl_fd("Error", 2);
	if (code == -1)
		ft_putendl_fd("Error: Map Character", 2);
	if (code == -2)
		ft_putendl_fd("Error: Doublon", 2);
	if (code == -3)
		ft_putendl_fd("Error: Donnée Manquante", 2);
	if (code == -4)
		ft_putendl_fd("Error: Map non rectangle", 2);
	if (code == -5)
		ft_putendl_fd("Error: Map non fermée", 2);
	if (code == -6)
		ft_putendl_fd("Error: Chemin non valide", 2);
	if (code == -7)
		ft_putendl_fd("Error: Image Loading", 2);
	return (code);
}

int	check_map(char **tab, t_data *data, int y_max)
{
	int	i;

	i = 0;
	if ((ft_strchr(tab[0], '1') == 1) || (ft_strchr(tab[y_max], '1') == 1))
		return (-5);
	if ((data->P) > 1 || (data->P) == 0 || (data->E) > 1 || (data->E) == 0
		|| data->collect < 1)
	{
		if ((data->P) > 1 || (data->E) > 1)
			return (-2);
		return (-3);
	}
	while (tab[i + 1])
	{
		if (ft_strlen(tab[i]) != ft_strlen(tab[i + 1]))
			return (-4);
		i++;
	}
	i = 0;
	while (tab[i])
	{
		if (tab[i][0] != '1' || tab[i][ft_strlen(tab[i]) - 1] != '1')
			return (-5);
		i++;
	}
	return (1);
}

char	**copy_tab(char **data_map, int lines)
{
	int	i;
	int	j;
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
		while(data_map[j][i])
		{
			map[j][i] = data_map[j][i];
			i++;
		}
		map[j][i] = 0;
		j++;
	}
	return (map);
}

void flood_fill(char **map, int y, int x) 
{
    if (map[y][x] == '1' || map[y][x] == 'X') 
        return;
    if (map[y][x] == '0' || map[y][x] == 'C' || map[y][x] == 'E' || map[y][x] == 'P') 
    {
        map[y][x] = 'X';
        flood_fill(map, y + 1, x);
        flood_fill(map, y - 1, x);
        flood_fill(map, y, x + 1);
        flood_fill(map, y, x - 1);
    }
}

int	check_finding(t_data *data)
{
	char	**copy;
	int	x;
	int	y;

	copy = copy_tab(data->tab, data->lines);
	if (!copy)
	{
		free_tab(copy);
		return (0);
	}
	x = data->player.x;
	y = data->player.y;
	flood_fill(copy, y, x);
	x = 0;
	y = 0;
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

int	set_rectangle(t_data *data, char **av)
{
	int	fd;
	int	i;

        fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		perror(av[1]);
		return (-9);
	}
        while (1)
        {
                i = 0;
                data->line = get_next_line(fd);
                if (!data->line)
		{
			close(fd);
                        break;
		}
                data->longueur = 0;
                while (data->line[i] != '\n')
                {
                        i++;
                        data->longueur += 64;
                }
                free(data->line);
                data->hauteur += 64;
        }
        if (data->hauteur == data->longueur)
                return (-4);
	else
	{
		data->lines = (data->hauteur / 64);
		return (1);
	}
}

void	put_bedrock(t_data *data)
{
mlx_put_image_to_window(data->mlx, data->win,
                                        data->bedrock.img_bedrock, data->longueur, data->hauteur);
}

void	put_dirt(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->dirt.img_dirt,
                                        data->longueur, data->hauteur);
}

void	put_diamond(t_data *data)
{
	data->collect += 1;
                                mlx_put_image_to_window(data->mlx, data->win,
                                        data->diamond.img_diamond, data->longueur, data->hauteur);
}

void	put_steve(t_data *data, int i, int j)
{
	data->player.x = i;
                                data->player.y = j;
                                data->P += 1;
                                mlx_put_image_to_window(data->mlx, data->win,
                                        data->steve.img_steve, data->longueur, data->hauteur);
}

void	put_portal(t_data *data)
{
	data->E += 1;
                                mlx_put_image_to_window(data->mlx, data->win,
                                        data->portal.img_portal, data->longueur, data->hauteur);
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
	{
		free(data->tab);
		return (0);
	}
	(data->tab)[data->lines] = 0;
	j = 0;
	data->collect = 0;
	data->P = 0;
	data->E = 0;
	data->hauteur = 0;
	data->longueur = 0;
	while (1)
        {
                i = 0;
                data->line = get_next_line(fd);
                if (!data->line)
                        break ;
                (data->tab)[j] = (char *)malloc(sizeof(char) * (ft_strlen(data->line)));
                while (data->line[i] != '\n')
                {
			if (put_img(data, data->line, i, j) == -1)
				return (-1);
                        (data->tab)[j][i] = data->line[i];
                        i++;
                        data->longueur += 64;
                }
                (data->tab)[j][i] = 0;
                j++;
                free(data->line);
                data->longueur = 0;
                data->hauteur += 64;
        }
	close(fd);
	return (1);
}

void	initmlx(char **av)
{
	t_data		data;

	data.lines = 0;
	data.longueur = 0;
	data.hauteur = 0;
	data.P = 0;
	data.E = 0;
	data.collect = 0;

	if (put_error(set_rectangle(&data, av)) <= 0 || put_error(init_data(&data, data.longueur, data.hauteur)) <= 0 || put_error(set_tab(&data, av)) <= 0 || put_error(check_map(data.tab, &data, ((data.lines) - 1))) <= 0 || put_error(check_finding(&data)) <= 0)
	{
		free_data(&data);
		return;
	}
	mlx_hook(data.win, 2, 1L << 0, move, &data);
	mlx_loop(data.mlx);
	free_data(&data);
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		// printmap(av);
		initmlx(av);
	}
	return (0);
}
