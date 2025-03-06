/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beade-va <beade-va@student.42.madrid>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:13:00 by beade-va          #+#    #+#             */
/*   Updated: 2025/03/06 12:16:29 by beade-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_and_accumulate(int fd, char *buffer)
{
	char	*buffer_temporary;
	int		bytes_read;
	char	*temp;

	buffer_temporary = malloc(BUFFER_SIZE + 1);
	if (!buffer_temporary)
		return (free(buffer), NULL);
	if (!buffer)
		buffer = ft_strdup("");
	bytes_read = 1;
	while (!ft_strchr(buffer, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer_temporary, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer_temporary), free(buffer), NULL);
		buffer_temporary[bytes_read] = '\0';
		temp = ft_strjoin(buffer, buffer_temporary);
		free(buffer);
		buffer = temp;
	}
	return (free(buffer_temporary), buffer);
}

static char	*extract_line(char *buffer)
{
	char	*newline;
	int		line_length;
	char	*extracted_line;

	if (!buffer || *buffer == '\0')
		return (NULL);
	newline = ft_strchr(buffer, '\n');
	if (newline)
		line_length = newline - buffer + 1;
	else
		line_length = ft_strlen(buffer);
	extracted_line = ft_substr(buffer, 0, line_length);
	return (extracted_line);
}

static char	*update_buffer(char *buffer)
{
	char	*new_buffer;
	int		line_length;
	char	*line_position;

	line_position = ft_strchr(buffer, '\n');
	if (line_position)
		line_length = line_position - buffer + 1;
	else
		line_length = ft_strlen(buffer);
	new_buffer = ft_substr(buffer, line_length, ft_strlen(buffer)
			- line_length);
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = read_and_accumulate(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	if (!*buffer[fd])
		return (free(buffer[fd]), buffer[fd] = NULL, NULL);
	line = extract_line(buffer[fd]);
	buffer[fd] = update_buffer(buffer[fd]);
	if (!buffer[fd] || !*buffer[fd])
		return (free(buffer[fd]), buffer[fd] = NULL, line);
	return (line);
}
