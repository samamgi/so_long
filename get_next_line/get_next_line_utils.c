/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <ssadi-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 22:53:47 by ssadi-ou          #+#    #+#             */
/*   Updated: 2024/11/27 00:18:00 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_gnl(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		i++;
	}
	return (i);
}

void	*ft_memchr_gnl(const char *s, int c)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (*str)
	{
		if (*str == (unsigned char)c)
			return (str);
		str++;
	}
	return (NULL);
}

char	*ft_strdup_gnl(char *s)
{
	int		i;
	char	*str;
	int		d;

	if (!s)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen_gnl(s) + 1));
	if (!str)
		return (NULL);
	i = 0;
	d = 1;
	while (s[i] && d > 0)
	{
		if (s[i] == '\n')
			d--;
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	j = -1;
	if (!s1)
		return (ft_strdup_gnl(s2));
	str = (char *)malloc(sizeof(char) * (ft_strlen_gnl(s1) + ft_strlen_gnl(s2)
				+ 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	while (s2[++j])
	{
		str[i] = s2[j];
		i++;
		if (s2[j] == '\n')
			break ;
	}
	str[i] = '\0';
	return (free(s1), str);
}

int	ft_strchr_gnl(char *str, char c)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
