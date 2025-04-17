/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 02:49:22 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/04/17 02:49:23 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

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
