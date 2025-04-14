/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <ssadi-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 23:25:01 by ssadi-ou          #+#    #+#             */
/*   Updated: 2024/11/27 00:17:13 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

int		ft_strlen_gnl(char *s);

void	*ft_memchr_gnl(const char *s, int c);

char	*ft_strdup_gnl(char *s);

char	*ft_strjoin_gnl(char *s1, char *s2);

int		ft_strchr_gnl(char *str, char c);

void	ft_putstr_fd_gnl(char *s, int fd);

char	*get_next_line(int fd);

#endif
