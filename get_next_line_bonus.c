/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-kha <yael-kha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:25:00 by yael-kha          #+#    #+#             */
/*   Updated: 2025/12/29 11:49:05 by yael-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*fill_line(int fd, char **what_left, char *buffer)
{
	char	*tmp;
	ssize_t	what_read;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	while (!ft_strchr(*what_left, '\n'))
	{
		what_read = read(fd, buffer, BUFFER_SIZE);
		if (what_read <= 0)
			break ;
		buffer[what_read] = '\0';
		tmp = ft_strjoin(*what_left, buffer);
		free(*what_left);
		*what_left = tmp;
		if (!*what_left)
			return (NULL);
	}
	return (*what_left);
}

char	*set_line(char *buffer_line, char **leftover)
{
	char	*line;
	size_t	i;

	i = 0;
	while (buffer_line[i] && buffer_line[i] != '\n')
		i++;
	if (buffer_line[i] == '\n')
		i++;
	line = ft_substr(buffer_line, 0, i);
	if (!line)
		return (free(buffer_line), NULL);
	*leftover = ft_substr(buffer_line, i, ft_strlen(buffer_line) - i);
	free(buffer_line);
	if (!*leftover)
		return (free(line), NULL);
	if (*(leftover)[0] == '\0')
	{
		free(*leftover);
		*leftover = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*what_left[1024];
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	if (!what_left[fd])
		what_left[fd] = ft_strdup("");
	if (!what_left[fd])
		return (NULL);
	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (free(what_left[fd]), what_left[fd] = NULL, NULL);
	what_left[fd] = fill_line(fd, &what_left[fd], buffer);
	free(buffer);
	if (!what_left[fd] || *what_left[fd] == '\0')
	{
		free(what_left[fd]);
		what_left[fd] = NULL;
		return (NULL);
	}
	line = set_line(what_left[fd], &what_left[fd]);
	return (line);
}
