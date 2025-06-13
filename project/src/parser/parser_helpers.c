/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:30:22 by lgottsch          #+#    #+#             */
/*   Updated: 2025/06/13 16:32:29 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	error_parsing(t_game *game, char *line, int fd)
{
	printf("Error: MAP FILE INVALID!!!\n");
	free(line);
	line = get_next_line(fd, 1);
	line = NULL;
	close (fd);
	free_everything(game, 1);
}

void	print_map(t_map *map)
{
	int	i;
	int	len;

	i = 0;
	while (i < map->map_height)
	{
		len = ft_strlen(map->map[i]);
		printf("Line %2d (%2d): \"%s\"\n", i, len, map->map[i]);
		i++;
	}
}
