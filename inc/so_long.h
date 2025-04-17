/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:26:08 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/04/17 02:20:42 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "so_long.h"
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

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

void				move_right(t_data *data);
void				move_down(t_data *data);

void				move_up(t_data *data);

void				free_tab(char **tab);

void				free_data(t_data *data);

int					close_window(t_data *data);

int					init_data(t_data *data, int longueur, int hauteur);

int					put_error(int code);

int					check_map(char **tab, t_data *data, int y_max);

char				**copy_tab(char **data_map, int lines);

void				flood_fill(char **map, int y, int x);

int					check_finding_util(char **copy, int y, int x);

int					check_finding(t_data *data);

int					set_rectangle_util(t_data *data, int fd);

int					set_rectangle(t_data *data, char **av);

void				put_bedrock(t_data *data);

void				put_dirt(t_data *data);

void				put_diamond(t_data *data);

void				put_steve(t_data *data, int i, int j);

void				put_portal(t_data *data);

int					put_img(t_data *data, char *line, int i, int j);

int					set_tab_util_2(t_data *data, int j, int i, int fd);

int					set_tab_util(t_data *data, int j, int i, int fd);

int					set_tab(t_data *data, char **av);

void				init_img_0(t_data *data);

void				init_data_0(t_data *data);

void				initmlx(char **av);

int					check_ber(char **av);

void				move_left(t_data *data);

int					move(int keycode, t_data *data);

#endif
