/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-13 14:28:34 by cpinho-c          #+#    #+#             */
/*   Updated: 2024-12-13 14:28:34 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static char	*read_file(int fd, char *buffer, char *stash);
static char	*get_line(char **stash);

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	stash = read_file(fd, buffer, stash);
	if (!stash)
	{
		free(buffer);
		return (NULL);
	}
	free(buffer);
	line = get_line(&stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	return (line);
}

static char	*read_file(int fd, char *buffer, char *stash)
{
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read > 0 && !(ft_strchr(stash, '\n')))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(stash);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		if (stash == NULL)
			stash = ft_strdup(buffer);
		else
		{
			temp = ft_strjoin(stash, buffer);
			stash = temp;
		}
	}
	return (stash);
}

static char	*get_line(char **stash)
{
	int		i;
	char	*temp;
	char	*line;

	i = 0;
	if (!*stash || **stash == '\0')
		return (NULL);
	while ((*stash)[i] && (*stash)[i] != '\n')
		i++;
	if (ft_strchr(*stash, '\n'))
	{
		temp = ft_substr(*stash, i + 1, ft_strlen(*stash));
		line = ft_substr(*stash, 0, i + 1);
		free(*stash);
		*stash = temp;
	}
	else
	{
		line = ft_strdup(*stash);
		free(*stash);
		*stash = NULL;
	}
	return (line);
}

// //read(fd, void *buffer, BUFFER_SIZE);
// #include <stdio.h>
// int main()
// {
// 	char *line;
// 	int fd = open("test.txt", O_RDONLY);
// 	if (fd < 0)
// 		return (1);
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return(0);
// }