/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <ssadi-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 22:51:09 by ssadi-ou          #+#    #+#             */
/*   Updated: 2024/11/27 00:17:11 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	rm_back(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			break ;
		i++;
	}
	i++;
	j = 0;
	while (str[i])
	{
		str[j] = str[i];
		i++;
		j++;
	}
	str[j] = '\0';
}

char	*get_next_line(int fd)
{
	char		*line;
	int			bytes;
	static char	buff[BUFFER_SIZE + 1] = {};

	if (BUFFER_SIZE < 1 || fd > 1024 || fd < 0)
		return (NULL);
	bytes = 1;
	line = NULL;
	if (ft_memchr_gnl(buff, '\n') != 0)
	{
		if (ft_strlen_gnl(ft_memchr_gnl(buff, '\n') + 1) > 0)
			line = ft_strdup_gnl(ft_memchr_gnl(buff, '\n') + 1);
		rm_back(buff);
	}
	while (bytes > 0 && (ft_strchr_gnl(line, '\n') == 0))
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		buff[bytes] = '\0';
		line = ft_strjoin_gnl(line, buff);
	}
	if (bytes <= 0 && !line)
		return (NULL);
	return (line);
}
