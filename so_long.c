/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:06:02 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/04/16 19:08:12 by ssadi-ou         ###   ########.fr       */
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
	int				p;
	int				e;
	int				lines;
	int				longueur;
	int				hauteur;
	int				moves;
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

void	free_data(t_data *data)
{
	if (data->mlx && data->win)
	{
		mlx_clear_window(data->mlx, data->win);
		mlx_destroy_window(data->mlx, data->win);
	}
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
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	if (data->tab)
		free_tab(data->tab);
	if (data->line)
		free(data->line);
	exit(0);
}

int	close_window(t_data *data)
{
	free_data(data);
	return (0);
}

int	init_data(t_data *data, int longueur, int hauteur)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, longueur, hauteur, "so_long");
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
		return ;
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
	ft_putstr_fd("Déplacements: ", 1);
	data->moves++;
	ft_putnbr_fd(data->moves, 1);
	ft_putchar_fd('\n', 1);
	return ;
}

void	move_down(t_data *data)
{
	if ((data->tab)[(data->player.y) + 1][data->player.x] == '1')
		return ;
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
	ft_putstr_fd("Déplacements: ", 1);
	data->moves++;
	ft_putnbr_fd(data->moves, 1);
	ft_putchar_fd('\n', 1);
	return ;
}

void	move_up(t_data *data)
{
	if ((data->tab)[(data->player.y) - 1][data->player.x] == '1')
		return ;
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
	ft_putstr_fd("Déplacements: ", 1);
	data->moves++;
	ft_putnbr_fd(data->moves, 1);
	ft_putchar_fd('\n', 1);
	return ;
}

void	move_left(t_data *data)
{
	if ((data->tab)[data->player.y][(data->player.x) - 1] == '1')
		return ;
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
	ft_putstr_fd("Déplacements: ", 1);
	data->moves++;
	ft_putnbr_fd(data->moves, 1);
	ft_putchar_fd('\n', 1);
	return ;
}

int	move(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		return (free_data(data), 0);
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
		ft_putstr_fd("The end !\n", 1);
		return (free_data(data), 0);
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
	if ((data->p) > 1 || (data->p) == 0 || (data->p) > 1 || (data->p) == 0
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

void	put_bedrock(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->bedrock.img_bedrock,
		data->longueur, data->hauteur);
}

void	put_dirt(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->dirt.img_dirt,
		data->longueur, data->hauteur);
}

void	put_diamond(t_data *data)
{
	data->collect += 1;
	mlx_put_image_to_window(data->mlx, data->win, data->diamond.img_diamond,
		data->longueur, data->hauteur);
}

void	put_steve(t_data *data, int i, int j)
{
	data->player.x = i;
	data->player.y = j;
	data->p += 1;
	mlx_put_image_to_window(data->mlx, data->win, data->steve.img_steve,
		data->longueur, data->hauteur);
}

void	put_portal(t_data *data)
{
	data->e += 1;
	mlx_put_image_to_window(data->mlx, data->win, data->portal.img_portal,
		data->longueur, data->hauteur);
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

void	init_img_0(t_data *data)
{
	data->dirt.img_dirt = NULL;
	data->diamond.img_diamond = NULL;
	data->bedrock.img_bedrock = NULL;
	data->steve.img_steve = NULL;
	data->portal.img_portal = NULL;
	data->dirt.img_h_dirt = 0;
	data->dirt.img_w_dirt = 0;
	data->diamond.img_h_diamond = 0;
	data->diamond.img_w_diamond = 0;
	data->bedrock.img_h_bedrock = 0;
	data->bedrock.img_w_bedrock = 0;
	data->steve.img_h_steve = 0;
	data->steve.img_w_steve = 0;
	data->portal.img_h_portal = 0;
	data->portal.img_w_portal = 0;
}

void	init_data_0(t_data *data)
{
	data->lines = 0;
	data->longueur = 0;
	data->hauteur = 0;
	data->p = 0;
	data->e = 0;
	data->collect = 0;
	data->moves = 0;
	data->player.x = 0;
	data->player.y = 0;
	data->mlx = NULL;
	data->win = NULL;
	data->tab = NULL;
	data->line = NULL;
	init_img_0(data);
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

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		if (ft_strlen(av[1]) == 0)
		{
			ft_putendl_fd("Error: No such file or directory", 2);
			return (0);
		}
		if (check_ber(av) == -1)
			return (0);
		initmlx(av);
	}
	else
		ft_putendl_fd("Error: Invalid Args !", 2);
	return (0);
}
