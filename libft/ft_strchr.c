/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <ssadi-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 00:59:32 by ssadi-ou          #+#    #+#             */
/*   Updated: 2024/11/10 01:09:59 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int     ft_strchr(char *str, char c)
{
        int     i;

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

