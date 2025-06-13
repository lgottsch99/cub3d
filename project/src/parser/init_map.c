/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025-06-12 10:20:06 by selango           #+#    #+#             */
/*   Updated: 2025-06-12 10:20:06 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "cub3d.h"
#include "../../includes/cub3d.h"

void	entire_map(int fd, char *line, t_map *map)
{
	int		i;
	char	*new_line;
	int		len;

	i = 0;
	len = 0;
	store_map(fd, line, map);
	map->map_width = map_width(map->map);
	map->map_height = map_height(map->map);
	printf("Original map dimension: %d, %d\n", map->map_width,
		map->map_height);
	while (i < map->map_height)
	{
		new_line = ft_strchr(map->map[i], '\n');
		if (new_line)
			*new_line = '\0';
		i++;
	}
	map->map = correct_map(map->map, map->map_width, map->map_height);
	map->map_width = map_width(map->map);
	printf("🟢 Corrected map:\n");
	print_map(map);
}

/* This store map function is used to store the map in the t_game map variable
	// I need to free map last*/
void	store_map(int fd, char *line, t_map *map)
{
	char	**grid;

	grid = NULL;
	if (!valid_map(line))
		return ;
	grid = malloc(sizeof(char *) * MAX_LINES);
	if (!grid)
		return ;
	if (store_map_utilis(fd, line, grid) == -1)
	{
		free(grid);
		return ;
	}
	map->map = grid;
}

/* Todo check how width was the map , check for the height of the map*/
/* GETTING THE MAP WIDTH FROM THE MAP*/
size_t	map_width(char **grid)
{
	size_t	map_width;
	size_t	current_width;
	int		i;
	int		j;

	map_width = 0;
	current_width = 0;
	i = 0;
	while (grid[i])
	{
		current_width = 0;
		j = 0;
		while (grid[i][j])
		{
			if (grid[i][j] == '\t')
				current_width += 4;
			else
				current_width++;
			j++;
		}
		if (map_width < current_width)
			map_width = current_width;
		i++;
	}
	return (map_width);
}

/* Checks the height of the map*/
size_t	map_height(char **grid)
{
	size_t	map_height;

	map_height = 0;
	while (grid[map_height])
	{
		map_height++;
	}
	return (map_height);
}

/* to do write the function that converts the tabs to spaces
// check for the len of the mapline and if the length is lesser than
 then your are going to reallocate the memory
// printf("Padding line %d from length %d to width %d\n", i, len, width);*/
char	**correct_map(char **strs, int width, int height)
{
	int	i;
	int	j;
	int	len;

	len = 0;
	i = 0;
	while (i < height)
	{
		j = 0;
		len = ft_strlen(strs[i]);
		if (len < width)
			ft_realloc_str((void **)&strs[i], len + 1, width + 1);
		tab_check(strs[i], &len);
		while (j < width)
		{
			if (j >= len)
				strs[i][j] = ' ';
			j++;
		}
		strs[i][width] = '\0';
		i++;
	}
	return (strs);
}
