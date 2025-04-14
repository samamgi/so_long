/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 04:24:41 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/04/14 04:30:11 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>

int	ft_strchr2(char *str, char c)
{
	int	i;

	i = 0;
	if (!str || ft_strlen(str) == 0)
		return (1);
	while (str[i])
	{
		if (str[i] != c)
			return (1);
		i++;
	}
	return (0);
}

int	main(void)
{
	printf("%i\n", ft_strchr("111111", '1'));
	printf("%i\n", ft_strchr2("111 11", '1'));
	return (0);
}
