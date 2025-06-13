/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025-05-29 12:50:39 by selango           #+#    #+#             */
/*   Updated: 2025-05-29 12:50:39 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*function parse the file to the struct as we defined.
It checks for the map first.
if map is not valid it parses the data to the check_data function.
valid_map if not valid->It process_line
in else map there is a entire map function which changes and
store the entire map*/
void	parse_data(int fd, t_game *game)
{
	char	*line;
	bool	detected_map;

	detected_map = false;
	line = get_next_line(fd, 0);
	init_game(game);
	while (line)
	{
		if (!valid_map(line))
		{
			printf("Line read: %s \n", line);
			if (process_line(line, game) == -1)
				error_parsing(game, line, fd);
		}
		else
		{
					printf("in map\n");

			if (detected_map == true)
				error_parsing(game, line, fd);
			detected_map = true;
			entire_map(fd, line, &game->map);
			// free(line);
		}
		printf("out of if/else\n");
		if (line)
			free(line);
		line = get_next_line(fd, 0);
	}
}

/* function parses the texture path to the corresponding texture 
from the map.cub*/
int	parse_texture(char *text_path, t_texture *texture, t_game *game)
{
	(void) game;
	if (texture->path)
	{
		return (1);
	}
	texture->path = ft_strdup(text_path);
	if (!texture->path)
	{
		return (1);
	}
	return (0);
}

// Forms args struct and then it assigns the values to R,G,B separately.
int	parse_color(char *value, t_color *color)
{
	char	**strs;
	int		count;

	count = 0;
	if (color->r != -1)
		return (1);
	if (ft_strchr_count(value, ',') != 2)
		return (1);
	strs = ft_split(value, ",");
	if (!strs || !validate_single_color(strs))
	{
		free_2d_array(strs);
		return (1);
	}
	while (strs[count])
		count++;
	if (count != 3)
	{
		free_2d_array(strs);
		printf("Three colors required for parsing colors");
		return (1);
	}
	assign_color(count, strs, color);
	free_2d_array(strs);
	return (0);
}

// then it 4 spaces copies into tab spaces.
// length  is increases to 4 since it adds the len
void	tab_check(char *strs, int *len)
{
	size_t	i;

	i = 0;
	while (strs[i] != '\0')
	{
		if (strs[i] == '\t')
		{
			ft_memmove(&strs[i + 4], &strs[i + 1], *len - i + 1);
			ft_strncpy(&strs[i], "    ", 4);
			*len += 3;
			i += 4;
		}
		else
			i++;
	}
}
