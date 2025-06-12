/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025-05-29 12:53:20 by selango           #+#    #+#             */
/*   Updated: 2025-05-29 12:53:20 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cub3d.h"
#include "../../includes/cub3d.h"

void	validate_texture(char *path, char *name)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (!path)
	{
		printf("Path Do not exit %s", path);
		exit(EXIT_FAILURE);
	}
	else if (!valid_extension(path, ".xpm"))
	{
		printf("Path do not support %s \n", name);
		exit(EXIT_FAILURE);
	}
	else if ((!fd))
	{
		printf("Cannot open the file %s %s", name, path);
		exit(EXIT_FAILURE);
	}
	else if (close(fd) == -1)
	{
		printf("Cannot close the file %s", path);
		exit(EXIT_FAILURE);
	}
	printf(" %s: %s\n", name, path);
}

/* if r ==-1 we assume the whole color is invalid. getting this create 
the color full visible if not you can make to 0*/
void	validate_color(t_color *color, char *side_name)
{
	if (color->r == -1)
		exit_error("color is invalid");
	else if (color->r > 255 || color->g > 255 || color->b > 255)
	{
		printf("Invalid color value %s", side_name);
		exit(EXIT_FAILURE);
	}
	color->full_color = create_new_color(255, color->r, color->g, color->b);
	printf("✅ %s: %d,%d,%d\n", side_name, color->r, color->g, color->b);
}

void	validate_map(t_map *map)
{
	char	**map_to_validate;
	int		new_width;
	int		expected_width;

	handle_invalid_map(map);
	expected_width = max_width(map->map, map->map_height);
	map_to_validate = handle_different_map(map, expected_width, &new_width);
	if (!is_map_enclosed(map_to_validate, map->map_height, new_width))
	{
		printf("Map enclosure check failed!\n");
		free_map_to_validate(map_to_validate, map->map);
		exit_error("Map is not enclosed");
	}
	else if (!single_player(map_to_validate))
	{
		free_map_to_validate(map_to_validate, map->map);
		exit_error("Map has more than one player or zero player");
	}
	free_map_to_validate(map_to_validate, map->map);
	map->map_width = new_width;
	printf("✅ Map validated. Size: %dx%d\n", map->map_width, map->map_height);
}

void	validate_game_data(t_game *game)
{
	validate_texture(game->no_texture.path, "NO texture");
	validate_texture(game->so_texture.path, "SO texture");
	validate_texture(game->ea_texture.path, "EA texture");
	validate_texture(game->we_texture.path, "WE texture");
	validate_color(&game->ceiling, "ceiling color");
	validate_color(&game->floor, "floor color");
	validate_map(&game->map);
}
