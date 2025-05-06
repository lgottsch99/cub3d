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

void parse_data(int fd, t_game *game)
{
   char *line;
   char **strs;
   init_game(game);
   line = 0;
   strs = 0;
   while(get_next_line(fd, &line))
   {    
    if(!valid_map(line))
    {
        /* This line checks the is_whitespaces present in the line*/
        strs = ft_split(line," \n\t\v\f\r");// changed the ft_split args
        check_data(strs,game);
        free_2d_array(strs);
        free(strs);
    }
    else
        handle_map(fd,line,game);// to do
   }
   free(line);
}




/* function parses the texture path to the corresponding texture from the map.cub*/
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
    /* checks if the value is set already?*/
    if(color->r != -1)
    {
        color->r = -1;
        return;
    }
    /*checks if the string has 2 commas inbetween */
    if(ft_strchr_count(value,',') != 2)
        return;
    strs = ft_split(value, ',');
    if(!strs)
        return;
    i = 0;
    while(strs[i] != 0)
    {
        if(!str_digit(strs[i]))
          return;
        i++;
    }
    if(i == 3)
    {
        color->r = ft_atoi(strs[0]);
        color->g = ft_atoi(strs[1]);
        color->b = ft_atoi(strs[2]);
    }
    
}