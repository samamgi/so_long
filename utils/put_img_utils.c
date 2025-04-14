/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_img_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 02:49:27 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/04/17 02:49:28 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

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
