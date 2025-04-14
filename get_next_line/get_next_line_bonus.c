/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <ssadi-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 22:51:09 by ssadi-ou          #+#    #+#             */
/*   Updated: 2024/11/27 01:48:36 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

char	*gnl(int fd, char **buff)
{
	char		*line;
	int			bytes;

	bytes = 1;
	line = NULL;
	if (ft_memchr(buff[fd], '\n') != 0)
	{
		if (ft_strlen(ft_memchr(buff[fd], '\n') + 1) > 0)
			line = ft_strdup(ft_memchr(buff[fd], '\n') + 1);
		rm_back(buff[fd]);
	}
	while (bytes > 0 && (ft_strchr(line, '\n') == 0))
	{
		bytes = read(fd, buff[fd], BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		buff[fd][bytes] = '\0';
		line = ft_strjoin(line, buff[fd]);
	}
	if (bytes <= 0 && !line)
		return (NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buff[FD_MAX] = {0};
	char		*result;

	if (BUFFER_SIZE < 1 || fd < 0 || fd > 1024)
		return (NULL);
	if (buff[fd] == NULL)
	{
		buff[fd] = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		buff[fd][0] = 0;
	}
	if (!buff[fd])
		return (NULL);
	result = gnl(fd, buff);
	if (!result)
	{
		free(buff[fd]);
		buff[fd] = NULL;
	}
	return (result);
}
