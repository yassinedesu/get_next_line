/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-kha <yael-kha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 01:41:17 by yael-kha          #+#    #+#             */
/*   Updated: 2025/12/20 15:43:42 by yael-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

char	*fill_line(int fd, char *what_left, char *buffer)
{
	char	*tmp;
	int		was_read;

	while (!ft_strchr(what_left, '\n'))
	{
		was_read = read(fd, buffer, BUFFER_SIZE);
		if (was_read <= 0)
			break ;
		buffer[was_read] = '\0';
		tmp = ft_strjoin(what_left, buffer);
		free(what_left);
		what_left = tmp;
		if (!what_left)
			return (NULL);
	}
	return (what_left);
}

char	*handling_fails(char **buffer)
{
	free(*buffer);
	return (NULL);
}

char	*set_line(char *buffer_line, char **left_c)
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
		return (handling_fails(&buffer_line));
	*left_c = ft_substr(buffer_line, i, ft_strlen(buffer_line) - i);
	free(buffer_line);
	if (!*left_c)
		return (handling_fails(&line));
	if ((*left_c)[0] == '\0')
	{
		free(*left_c);
		*left_c = NULL;
	}
	return (line);
}

char *get_next_line(int fd)
{
	static char	*what_left;
	char	*buffer;
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!what_left)
		what_left = ft_strdup("");
	if (!what_left)
		return (NULL);
	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	what_left = fill_line(fd, what_left, buffer);
	free(buffer);
	if (!what_left || what_left[0] == '\0')
	{
		free(what_left);
		what_left = NULL;
		return (NULL);
	}
	line = set_line(what_left, &what_left);
	return (line);
}

int main()
{
	// Example usage of get_next_line
	int fd = open("example.txt", O_RDONLY | O_CREAT, 0644);
	char *line;

	if (fd == -1)
		return (1);

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}

