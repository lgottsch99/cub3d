/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-07 10:05:30 by selango           #+#    #+#             */
/*   Updated: 2025-05-07 10:05:30 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int valid_map(char *grid)
{
    int map_value;
    map_value =0;
    while(*grid)
    {
        if(!ft_strchr("01NESW  \n\t\v\f\r", *grid))
            return(0);
        else if(*grid == '1')
            map_value = 1;
        grid++;
    }
    return(map_value);
}

void init_game(t_game *game)
{
    ft_memset(game,0,sizeof(t_game));
    ft_memset(&game->ceiling, -1, sizeof(t_color));
    ft_memset(&game->floor, -1 , sizeof(t_color));
}


// This function checks whether the map has the correct data and parse them 
void check_data(char **strs, t_game *game)
{
    if(strs[0] == 0)
        return;
    else if (!ft_strcmp(strs[0], "NO") && strs[1] != 0 && strs[2] == 0)
        parse_texture(strs[1], &game->No_texture);
   else if (!ft_strcmp(strs[0], "SO") && strs[1] != 0 && strs[2] == 0)
        parse_texture(strs[1], &game->So_texture);   
    else if (!ft_strcmp(strs[0], "WE") && strs[1] != 0 && strs[2] == 0)
        parse_texture(strs[1], &game->We_texture);
    else if (!ft_strcmp(strs[0], "EA") && strs[1] != 0 && strs[2] == 0)
        parse_texture(strs[1], &game->Ea_texture);
    else if(!ft_strcmp(strs[0], "F") && strs[1] != 0 && strs[2] == 0)
        parse_color(strs[1],&game->floor);
    else if(!ft_strcmp(strs[0], "C") && strs[1] != 0 && strs[2] == 0)
        parse_color(strs[1],&game->ceiling);
    /* to check unknown identifier*/
    else if(strs[0][0] != '\n')
    {
        exit_error(strs[0]);
        exit(EXIT_SUCCESS);
    }  
}
