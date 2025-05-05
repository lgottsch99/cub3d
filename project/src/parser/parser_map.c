/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-05 11:11:33 by selango           #+#    #+#             */
/*   Updated: 2025-05-05 11:11:33 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

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
}
void parse_texture(char *text_path,t_texture *texture)
{
    if(!texture->path)
        texture->path = ft_strdup(text_path);
    else
        texture->path = NULL;
}
//Forms args struct and then it assigns the values to R,G,B separately.
void parse_color(char *value,t_color *color)
{
    int i;
    char **strs;
    
    if(color->r != -1)
    {
        color->r == -1;
        return;
    }
    //checks if the string has 2 commas inbetween
    if(ft_strchr_count(value,',') != 2)
        return;
    strs = ft_split(value, ',');
    if(!strs)
        return;
    i =0;
// TODO 
    while(strs[i] != 0  && )
    if(strs == 3)
    {
        ft_atoi(strs[1])
    }
    


}