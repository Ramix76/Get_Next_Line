/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 17:24:53 by framos-p          #+#    #+#             */
/*   Updated: 2022/07/18 10:04:37 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*extract_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[0])
		return (NULL);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\0')
		line = malloc((i + 1) * sizeof(char));
	else
		line = malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*fill_static_buffer(char *buffer, int fd)
{
	char	*read_buffer_size;
	int		num_bytes;

	read_buffer_size = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!read_buffer_size)
		return (NULL);
	read_buffer_size[0] = '\0';
	num_bytes = 1;
	while (num_bytes > 0 && !ft_strchr(read_buffer_size, '\n'))
	{
		num_bytes = read(fd, read_buffer_size, BUFFER_SIZE);
		if (num_bytes > 0)
		{
			read_buffer_size[num_bytes] = '\0';
			buffer = ft_strjoin(buffer, read_buffer_size);
		}
	}
	free(read_buffer_size);
	if (num_bytes == -1)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

static char	*clean_buffer(char *buffer)
{
	int		i;
	int		j;
	char	*new_buffer;

	i = 0;
	j = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	i++;
	new_buffer = malloc((ft_strlen(buffer) + 1) * sizeof(char));
	if (!new_buffer)
		return (NULL);
	while (buffer[i] != '\0')
		new_buffer[j++] = buffer[i++];
	new_buffer[j] = '\0';
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1023)
		return (NULL);
	if (!buffer[fd] || (buffer[fd] && !ft_strchr(buffer[fd], '\n')))
		buffer[fd] = fill_static_buffer(buffer[fd], fd);
	if (!buffer[fd])
		return (NULL);
	line = extract_line(buffer[fd]);
	buffer[fd] = clean_buffer(buffer[fd]);
	return (line);
}
