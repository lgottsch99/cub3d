/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:27:18 by selango           #+#    #+#             */
/*   Updated: 2025/06/12 16:21:26 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cub3d.h"

#include "../../includes/cub3d.h"

void	handle_invalid_map(t_map *map)
{
	if (!map->map)
		exit_error("Invalid or empty map");
}

char	**handle_different_map(t_map *map, int expected_width, int *new_width)
{
	char	**map_to_validate;
	size_t	new_width;

	if (!is_rectangular(map->map, map->map_height, expected_width))
	{
		map_to_validate = normalize_map(map->map, map->map_height, new_width);
		printf("Normalized map content:\n");
		print_map_normalize(map->map_height, map_to_validate);
	}
	else
	{
		map_to_validate = map->map;
		new_width = ft_strlen(map->map[0]);
		printf("Original map content:\n");
		print_map_normalize(map->map_height, map_to_validate);
	}
	return (map_to_validate);
}

void	print_map_normalize(int height, char **map)
{
	int	i;
	int	len;

	i = 0;
	while (i < height)
	{
		len = ft_strlen(map[i]);
		printf("Line %2d (%2d): \"%s\"\n", i, len, map[i]);
		i++;
	}
}
