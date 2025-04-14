/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:06:02 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/04/14 02:49:45 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line/get_next_line.h"
#include "libft/libft.h"
#include <X11/keysym.h>

int	printmap(char **av)
{
	char    *line;
        int     fd;

                fd = open(av[1], O_RDONLY);
                while (1)
                {
                        line = get_next_line(fd);
                        ft_putstr_fd(line, 1);
                        if (!line)
                                break;
                        free(line);
                }
                close(fd);
		return (fd);
}

int	close_window(void *win)
{
	(void)win;
	exit(0);
	return (0);
}

typedef struct s_player
{
        int     x;  
        int     y;  
}t_player;

typedef struct s_img_dirt
{
	void    *img_dirt;
	int     img_w_dirt;
        int     img_h_dirt;
}t_img_dirt;

typedef struct s_img_diamond
{
        void    *img_diamond;
        int     img_w_diamond;
        int     img_h_diamond;
}t_img_diamond;

typedef struct s_img_bedrock
{
        void    *img_bedrock;
        int     img_w_bedrock;
        int     img_h_bedrock;
}t_img_bedrock;

typedef struct s_img_steve
{
        void    *img_steve;
        int     img_w_steve;
        int     img_h_steve;
}t_img_steve;

typedef struct s_img_portal
{
        void    *img_portal;
        int     img_w_portal;
        int     img_h_portal;
}t_img_portal;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img_dirt	dirt;
	t_img_diamond	diamond;
	t_img_bedrock	bedrock;
	t_img_steve	steve;
	t_img_portal	portal;
	t_player 	player;
	char		**tab;
	int		collect;
}t_data;

int	move(int keycode, t_data *data)
{
        printf("%i\n%i\n", data->player.y, data->player.x);
	if (keycode == 65307)
		exit (0);
	if (keycode == 'd')
	{
		if (((data->tab)[data->player.y][(data->player.x) + 1] == '1') || (((data->tab)[data->player.y][(data->player.x) + 1] == 'E') && (data->collect != 0)))
			return (1);
		printf("check\n");
		mlx_put_image_to_window(data->mlx, data->win, data->dirt.img_dirt, ((data->player.x) * 64), ((data->player.y) * 64));
		(data->player.x) += 1;
		mlx_put_image_to_window(data->mlx, data->win, data->steve.img_steve, ((data->player.x) * 64), ((data->player.y) * 64));
	}
	if (keycode == 's')
        {       
		if (((data->tab)[(data->player.y) + 1][data->player.x] == '1') || (((data->tab)[(data->player.y) + 1][data->player.x] == 'E') && (data->collect != 0)))

			return (1);
                printf("check\n");
                mlx_put_image_to_window(data->mlx, data->win, data->dirt.img_dirt, ((data->player.x) * 64), ((data->player.y) * 64));
                (data->player.y) += 1;
                mlx_put_image_to_window(data->mlx, data->win, data->steve.img_steve, ((data->player.x) * 64), ((data->player.y) * 64));
        }
	if (keycode == 'w')
        {       
		if (((data->tab)[(data->player.y) - 1][data->player.x] == '1') || (((data->tab)[(data->player.y) - 1][data->player.x] == 'E') && (data->collect != 0)))
			return (1);
                printf("check\n");
                mlx_put_image_to_window(data->mlx, data->win, data->dirt.img_dirt, ((data->player.x) * 64), ((data->player.y) * 64));
                (data->player.y) -= 1;
                mlx_put_image_to_window(data->mlx, data->win, data->steve.img_steve, ((data->player.x) * 64), ((data->player.y) * 64));
        }
	if (keycode == 'a')
        {      
		if (((data->tab)[data->player.y][(data->player.x) - 1] == '1') || (((data->tab)[data->player.y][(data->player.x) - 1] == 'E') && (data->collect != 0)))
			return (1);
                printf("check\n");
                mlx_put_image_to_window(data->mlx, data->win, data->dirt.img_dirt, ((data->player.x) * 64), ((data->player.y) * 64));
                (data->player.x) -= 1;
                mlx_put_image_to_window(data->mlx, data->win, data->steve.img_steve, ((data->player.x) * 64), ((data->player.y) * 64));
        }
	if ((data->tab)[data->player.y][data->player.x] == 'C')
	{
		(data->tab)[data->player.y][data->player.x] = '0';
		data->collect -= 1;
	}
	printf("collectibles restants: %i\n", data->collect);
	if (((data->tab)[data->player.y][data->player.x] == 'E') && ((data->collect) == 0))
		exit (0);
	return (1);
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

void	initmlx(char **av)
{
	int	i;
	int	j;
	int	longueur;
	int	hauteur;
	char	*line;
	int	fd1;
	int	fd2;
	t_data	data;
	t_player player;

	longueur = 0;
	hauteur = 0;	
	fd1 = open(av[1], O_RDONLY);
	fd2 = open(av[1], O_RDONLY);
	while (1)
        {
                i = 0;
                line = get_next_line(fd1);
                if (!line)
                        break;
		longueur = 0;
                while (line[i] != '\n')
                {
                        i++;
                        longueur += 64;
                }
                free(line);
                hauteur += 64;
        }
	printf("%i\n", longueur);
	printf("%i\n", hauteur);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, longueur, hauteur, "so_long");
	mlx_hook(data.win, 17, 0, close_window, NULL);
	data.dirt.img_dirt = mlx_xpm_file_to_image(data.mlx, "dirt.xpm", &(data.dirt.img_w_dirt), &(data.dirt.img_h_dirt));
	data.diamond.img_diamond = mlx_xpm_file_to_image(data.mlx, "diamond.xpm", &(data.diamond.img_w_diamond), &(data.diamond.img_h_diamond));
	data.bedrock.img_bedrock = mlx_xpm_file_to_image(data.mlx, "bedrock.xpm", &(data.bedrock.img_w_bedrock), &(data.bedrock.img_h_bedrock));
	data.steve.img_steve= mlx_xpm_file_to_image(data.mlx, "steve.xpm", &(data.steve.img_w_steve), &(data.steve.img_h_steve));
	data.portal.img_portal = mlx_xpm_file_to_image(data.mlx, "portal.xpm", &(data.portal.img_w_portal), &(data.portal.img_h_portal));
	if (!data.steve.img_steve || !data.dirt.img_dirt || !data.diamond.img_diamond || !data.bedrock.img_bedrock || !data.portal.img_portal)
	{
		ft_putendl_fd("Error", 2);
		return;
	}
	j = (hauteur / 64);
	hauteur = 0;
	longueur = 0;
	data.tab = (char **)malloc(sizeof(char *) * j + 1);
        (data.tab)[j] = 0;
	j = 0;
	data.collect = 0;
	while (1)
	{
		i = 0;
		line = get_next_line(fd2);
		if (!line)
			break;
		(data.tab)[j] = (char *)malloc(sizeof(char) * (ft_strlen(line)));
		while (line[i] != '\n')
		{
			if (line[i] == '1')
				mlx_put_image_to_window(data.mlx, data.win, data.bedrock.img_bedrock, longueur, hauteur);
			if (line[i] == '0')
				mlx_put_image_to_window(data.mlx, data.win, data.dirt.img_dirt, longueur, hauteur);
			if (line[i] == 'C')
			{
				data.collect += 1;
				mlx_put_image_to_window(data.mlx, data.win, data.diamond.img_diamond, longueur, hauteur);
			}
			if (line[i] == 'P')
			{
				player.x = i;
				player.y = j;
				mlx_put_image_to_window(data.mlx, data.win, data.steve.img_steve, longueur, hauteur);
			}
			if (line[i] == 'E')
				mlx_put_image_to_window(data.mlx, data.win, data.portal.img_portal, longueur, hauteur);
			(data.tab)[j][i] = line[i];
			i++;
			longueur += 64;
		}
		(data.tab)[j][i] = 0;
		j++;
		free(line);
		longueur = 0;
		hauteur += 64;
	}
	printf("%i\n", data.collect);
	data.player = player;
	print_tab(data.tab);
	mlx_hook(data.win, 2, 1L<<0, move, &data);
	mlx_loop(data.mlx);
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		printmap(av);
		initmlx(av);
	}
	return (0);
}
