/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beade-va <beade-va@student.42.madrid>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:54:43 by beade-va          #+#    #+#             */
/*   Updated: 2025/02/19 21:48:42 by beade-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_accumulate(int fd, char *buffer)
{
	char	*buffer_temporary;
	int		bytes_read;
	char	*temp;

	buffer_temporary = malloc(BUFFER_SIZE + 1);
	if (!buffer_temporary)
		return (NULL);
	if (!buffer)
		buffer = ft_strdup("");
	bytes_read = 1;
	while (!ft_strchr(buffer, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer_temporary, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer_temporary);
			return (NULL);
		}
		buffer_temporary[bytes_read] = '\0';
		temp = ft_strjoin(buffer, buffer_temporary);
		free(buffer);
		buffer = temp;
	}
	free(buffer_temporary);
	return (buffer);
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
	static char	*buffer;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_and_accumulate(fd, buffer);
	if (!buffer || *buffer == '\0')
	{
		free(buffer);
		return (NULL);
	}
	line = extract_line(buffer);
	temp = update_buffer(buffer);
	buffer = temp;
	return (line);
}
