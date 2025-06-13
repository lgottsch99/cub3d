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

void	validate_texture(char *path, char *name, t_game *game)
{
	int	fd;

	if (!path)
	{
		printf("Path Do not exit %s", path);
		free_everything(game, 1);
	}
	fd = open(path, O_RDONLY);
	if (!valid_extension(path, ".xpm"))
	{
		printf("Path do not support %s \n", name);
		free_everything(game, 1);
	}
	else if ((!fd))
	{
		printf("Cannot open the file %s %s", name, path);
		free_everything(game, 1);
	}
	else if (close(fd) == -1)
	{
		printf("Cannot close the file %s", path);
		free_everything(game, 1);
	}
	printf(" %s: %s\n", name, path);
}

/* if r ==-1 we assume the whole color is invalid. getting this create 
the color full visible if not you can make to 0*/
void	validate_color(t_color *color, char *side_name, t_game *game)
{
	if (color->r == -1)
		exit_error("color is invalid", game);
	else if (color->r > 255 || color->g > 255 || color->b > 255)
	{
		printf("Invalid color value %s", side_name);
		exit_error("", game);
	}
	color->full_color = create_new_color(255, color->r, color->g, color->b);
	printf("✅ %s: %d,%d,%d\n", side_name, color->r, color->g, color->b);
}

void	validate_map(t_map *map, t_game *game)
{
	char	**map_to_validate;
	int		new_width;
	int		expected_width;

	handle_invalid_map(map, game);
	expected_width = max_width(map->map, map->map_height);
	map_to_validate = handle_different_map(map, expected_width, &new_width);
	if (!is_map_enclosed(map_to_validate, map->map_height, new_width))
	{
		printf("Map enclosure check failed!\n");
		free_map_to_validate(map_to_validate, map->map);
		exit_error("Map is not enclosed", game);
	}
	else if (!single_player(map_to_validate))
	{
		free_map_to_validate(map_to_validate, map->map);
		exit_error("Map has more than one player or zero player", game);
	}
	free_map_to_validate(map_to_validate, map->map);
	map->map_width = new_width;
	printf("✅ Map validated. Size: %dx%d\n", map->map_width, map->map_height);
}

void	validate_game_data(t_game *game)
{
	validate_texture(game->no_texture.path, "NO texture", game);
	validate_texture(game->so_texture.path, "SO texture", game);
	validate_texture(game->ea_texture.path, "EA texture", game);
	validate_texture(game->we_texture.path, "WE texture", game);
	validate_color(&game->ceiling, "ceiling color", game);
	validate_color(&game->floor, "floor color", game);
	validate_map(&game->map, game);
}
