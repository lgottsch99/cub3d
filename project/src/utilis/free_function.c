/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:52:39 by selango           #+#    #+#             */
/*   Updated: 2025/06/12 16:34:33 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cub3d.h"
#include "../../includes/cub3d.h"

void free_game(t_game *game)
{
    if(game->No_texture.path)
        free(game->No_texture.path);
    if(game->So_texture.path)
        free(game->So_texture.path);
    if(game->We_texture.path)
        free(game->We_texture.path);
    if(game->Ea_texture.path)
        free(game->Ea_texture.path);
    if(game->map.map)
        free_2d_array(game->map.map); 
}


void	free_2d_array(char **strs)
{
	char **temp = strs;
	while (*temp)
	{
		free(*temp);
		temp++;
	}
	if(strs)
		free(strs);
}

void free_process_line(char *trimmed,char *value,char *id,char **strs)
{
    if(trimmed)
        free(trimmed);
    if(value)
        free(value);
    if(id)
        free(id);
    if(strs)
        free_2d_array(strs);
}

void free_map_to_validate(char **grid,char **map)
{
	 if (grid != map)
            free_2d_array(grid);
}