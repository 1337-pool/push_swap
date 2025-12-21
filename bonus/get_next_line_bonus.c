/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaber <mjaber@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 17:00:00 by mjaber            #+#    #+#             */
/*   Updated: 2025/12/21 00:00:00 by mjaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

static char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*result;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	i = 0;
	while (s1[i])
		i++;
	j = 0;
	while (s2[j])
		j++;
	result = malloc(i + j + 1);
	if (!result)
		return (free(s1), NULL);
	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	j = -1;
	while (s2[++j])
		result[i + j] = s2[j];
	result[i + j] = '\0';
	return (free(s1), result);
}

static char	*extract_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer || !buffer[0])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*update_buffer(char *buffer)
{
	char	*new_buffer;
	int		i;
	int		j;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free(buffer), NULL);
	i++;
	if (!buffer[i])
		return (free(buffer), NULL);
	j = 0;
	while (buffer[i + j])
		j++;
	new_buffer = malloc(j + 1);
	if (!new_buffer)
		return (free(buffer), NULL);
	j = 0;
	while (buffer[i + j])
	{
		new_buffer[j] = buffer[i + j];
		j++;
	}
	new_buffer[j] = '\0';
	return (free(buffer), new_buffer);
}

static void	cleanup_buffer(char **buffer)
{
	if (buffer && *buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	char		*temp;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (cleanup_buffer(&buffer), NULL);
	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (cleanup_buffer(&buffer), NULL);
	bytes_read = 1;
	while (!ft_strchr(buffer, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(temp), cleanup_buffer(&buffer), NULL);
		temp[bytes_read] = '\0';
		buffer = ft_strjoin_gnl(buffer, temp);
		if (!buffer)
			return (free(temp), NULL);
	}
	free(temp);
	line = extract_line(buffer);
	buffer = update_buffer(buffer);
	if (!line)
		cleanup_buffer(&buffer);
	return (line);
}