/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-03 10:46:39 by selango           #+#    #+#             */
/*   Updated: 2024-07-03 10:46:39 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../full_libft.h"

static char	*read_lines(int fd, char *buff, char *store)
{
	int		bytes;
	char	*temp;

	bytes = 1;
	while (bytes)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
			return (0);
		else if (bytes == 0)
			break ;
		buff[bytes] = '\0';
		if (!store)
			store = ft_strdup("");
		temp = store;
		store = ft_strjoin(temp, buff);
		if (!store)
			return (NULL);
		free(temp);
		temp = NULL;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (store);
}

static char	*update(char *lines)
{
	int		i;
	char	*temp;

	i = 0;
	while (lines[i] != '\0' && lines[i] != '\n')
		i++;
	if (lines[i] == '\0')
		return (NULL);
	temp = ft_substr(lines, i + 1, ft_strlen(lines) - i);
	if (!temp)
		return (NULL);
	if (temp[0] == '\0')
	{
		free(temp);
		temp = NULL;
		return (NULL);
	}
	lines[i + 1] = '\0';
	return (temp);
}

char	*get_next_line(int fd,char **line)
{
	char		*buff;
	char		*lines;
	static char	*store;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (-1);
	lines = read_lines(fd, buff, store);
	free(buff);
	if (!lines)
		return (0);
	store = update(lines);
	*line = lines;
	return (1);
}

// #include <fcntl.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("file.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s\n", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }