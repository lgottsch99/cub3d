/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utilis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-13 13:22:02 by selango           #+#    #+#             */
/*   Updated: 2025-05-13 13:22:02 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cub3d.h"
#include "../../includes/cub3d.h"

int valid_extension(char *path,char *extension)
{
    size_t len_path;
    size_t ext_len;

    len_path = ft_strlen(path);
    ext_len = ft_strlen(extension);
    if(!path || !extension)
        return(0);
    else if(len_path >= ext_len && ft_strcmp(&path[len_path -ext_len],extension) == 0)
    {
        return(1);
    }
    return(0);
}
int create_new_color(int a,int r, int g, int b)
{
    return(a << 24 | r << 16 | g << 8 | b);
}
/* this function ensures that it is enclosed with the 1 
    it checks for the boundary checks in the map
    checks all the 4 directions if it is not a space*/
int is_map_enclosed(char **map,int height, int width)
{
    printf("🟡 Entered is_map_enclosed()\n");
    int i ;
    int j;

    i =0;
    while (i < height)
    {
        j = 0;
        while(j < width)
        {
            char c = map[i][j];
            if(!is_valid_char(c))
            {
                printf("❌ Invalid character '%c' at (%d, %d)\n", c, i, j);
                return(0);
            }
            if(c == '0' || ft_strchr("NSEW",c))
            {
                if(i == 0 || j == 0 || i == (height -1) || j >= (width -1))
                {
                    printf("❌ Walkable tile on edge at (%d, %d)\n", i, j);
                    return(0);
                }
                if(map[i -1][j] == ' ' || map[i+ 1][j] == ' ' || map[i] [j -1] == ' ' || map[i][j + 1] == ' ')
                {
                    printf("Map not enclosed at (%d, %d), char='%c'\n", i, j, map[i][j]);
                    return(0);
                }
            }
            j++;
        }
        i++;
    }
    return(1);
}
int single_player(char **map)
{
    int i ;
    int j ;
    int count;

    count = 0;
    i = 0;
    while(map[i])
    {
        j = 0;
        while(map[i][j])
        {
            if(ft_strchr("NSEW",map[i][j]))
                count++;
            j++;
        }
        i++;
    }
    if(count != 1)
        return(0);
    return(1);
}



void trim_crlf(char *line)
{
    char *p = line;
    while (*p)
    {
        if (*p == '\r' || *p == '\n')
        {
            *p = '\0';
            break;
        }
        p++;
    }
}



