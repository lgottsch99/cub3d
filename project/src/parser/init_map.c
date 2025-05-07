/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-06 09:43:45 by selango           #+#    #+#             */
/*   Updated: 2025-05-06 09:43:45 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void entire_map(int fd, char *line,t_map *map)
{
    store_map(fd,line,map);
    map->map_width = map_width(map);
    map->map_height = map_height(map);  
}

/* This store map function is used to store the map in the t_game map variable // I need to free map last*/
void store_map(int fd,char *line,t_map *map)
{
    char **grid;
    char *single_value;
    int count ;

    count =0 ;
    grid = NULL;
    single_value = line;
    if(!valid_map(line))
        return;
    grid = malloc(sizeof(char *) * MAX_LINES);
    if(!grid)
        return NULL;
    while (line && count < MAX_LINES)
    {
       grid[count] = ft_strdup(single_value);
       count++;
       free(single_value);
       if(!get_next_line(fd, &single_value))
            break;
    }
    grid[count] =  NULL;
    map->map = grid;
}

/* Todo check how width was the map , check for the height of the map*/
/* GETTING THE MAP WIDTH FROM THE MAP*/
size_t map_width(char **grid)
{
    size_t map_width;
    size_t current_width;
    int i;
    int j;

    map_width = 0;
    current_width = 0;
    i = 0;
    j = 0;
    while(grid[i][j])
    {
        if(grid[i][j] == '\t')
            current_width += 4;
        else    
            current_width++;
        j++;
    }
    if(map_width < current_width)
        map_width = current_width;
    i++;
    return(map_width);
}
/* Checks the height of the map*/
size_t map_height(char **grid)
{
    size_t map_height;

    map_height =0;
    while(grid[map_height])
    {
       map_height++;
    }
    return (map_height);
}
/* to do write the function that converts the tabs to spaces*/
char **correct_map(char **strs,int width, int height)
{
    int i;
    int j;
    int len;
    
    len =0;
    i =0;
    while (i < height)
    {
        j =0;
        len = ft_strlen(strs[i]);//check for the len of the mapline and if the length is lesser than then your are going to reallocate the memory
        if(len < width)
            ft_realloc_str((void **)&strs[i],len + 1, width + 1);// todo
        while (j < width)
        {
            if(strs[i][j] == '\t')
            {
                ft_memmove(&strs[i][j + 4], &strs[i][j + 1],len - j + 2);//  memmove function todo why not using memcpy?
                ft_strncpy(&strs[i][j],'\t', 4);
                len +=4;
            }
            else if ( j >= len)
                strs[i][j] = ' ';
        }
        strs[i][j] = '\0';
    }
    return (strs);
}

