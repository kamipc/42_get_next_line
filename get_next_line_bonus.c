/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-17 13:05:44 by cpinho-c          #+#    #+#             */
/*   Updated: 2024-12-17 13:05:44 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

static char	*read_file(int fd, char *buffer, char *stash);
static char	*get_line(char **stash);

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	stash[fd] = read_file(fd, buffer, stash[fd]);
	if (!stash[fd])
	{
		free(buffer);
		return (NULL);
	}
	free(buffer);
	line = get_line(&stash[fd]);
	if (!line)
	{
		free(stash[fd]);
		stash[fd] = NULL;
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

// int	main(void){
// 	int	fd1, fd2;
// 	char	*line;
// 	fd1 = open("test.txt", O_RDONLY);
// 	fd2 = open("test1.txt", O_RDONLY);
// 	while (1)
// 	{
// 		line = get_next_line(fd1);
// 		if (line)
// 		{
// 			printf("test: %s", line);
// 			free(line);
// 		}
// 		line = get_next_line(fd2);
// 		if (line)
// 		{
// 			printf("test2: %s", line);
// 			free(line);
// 		}
// 		if (line == NULL && get_next_line(fd1) == NULL 
// 			 && get_next_line(fd2) == NULL)
// 			break;
// 	}
// 	close(fd1);
// 	close(fd2);
// 	return (0);
// }