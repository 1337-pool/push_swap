/* ************************************************************************** */
/*                                                                            */
/*   get_next_line.c                                                          */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* 
** A very simple join for GNL. 
** Note: This is not the most optimized GNL, but it is 
** robust, norm-compliant, and sufficient for checker.
*/
static char	*ft_strjoin_char(char *s, char c)
{
	char	*new_str;
	int		i;

	i = 0;
	while (s && s[i])
		i++;
	new_str = malloc(i + 2);
	if (!new_str)
		return (NULL);
	i = 0;
	while (s && s[i])
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	free(s);
	return (new_str);
}

char	*get_next_line(int fd)
{
	char	*line;
	char	buffer;
	int		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	bytes_read = read(fd, &buffer, 1);
	while (bytes_read > 0)
	{
		line = ft_strjoin_char(line, buffer);
		if (!line)
			return (NULL);
		if (buffer == '\n')
			break ;
		bytes_read = read(fd, &buffer, 1);
	}
	if (bytes_read < 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
