/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-kha <yael-kha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:25:00 by yael-kha          #+#    #+#             */
/*   Updated: 2025/12/17 17:00:16 by yael-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

char	*_fill_line_buffer(int fd, char *left_c, char *buffer)
{
    int		bytes_read;
    char	*temp;

    while (!ft_strchr(left_c, '\n'))
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read <= 0)
            break ;
        buffer[bytes_read] = '\0';
        temp = ft_strjoin(left_c, buffer);
        free(left_c);
        left_c = temp;
        if (!left_c)
            return (NULL);
    }
    return (left_c);
}

char	*_set_line(char *line_buffer)
{
    char	*line;
    char	*remaining;
    size_t	i;

    i = 0;
    while (line_buffer[i] && line_buffer[i] != '\n')
        i++;
    if (line_buffer[i] == '\n')
        i++;
    line = ft_substr(line_buffer, 0, i);
    remaining = ft_substr(line_buffer, i, ft_strlen(line_buffer) - i);
    free(line_buffer);
    if (remaining && remaining[0] == '\0')
    {
        free(remaining);
        remaining = NULL;
    }
    return (line);
}

char	*get_next_line(int fd)
{
    static char	*left_c;
    char		buffer[BUFFER_SIZE + 1];
    char		*line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    if (!left_c)
        left_c = ft_strdup("");
    if (!left_c)
        return (NULL);
    left_c = _fill_line_buffer(fd, left_c, buffer);
    if (!left_c || left_c[0] == '\0')
    {
        free(left_c);
        left_c = NULL;
        return (NULL);
    }
    line = _set_line(left_c);
    left_c = NULL;
    return (line);
}
