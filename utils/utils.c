/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 02:49:43 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/04/17 02:49:44 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

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
