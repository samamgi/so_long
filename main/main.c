/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:06:02 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/04/17 02:12:27 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

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
