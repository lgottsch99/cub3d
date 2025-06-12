/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utilis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-06 11:56:36 by selango           #+#    #+#             */
/*   Updated: 2025-06-06 11:56:36 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cub3d.h"
#include "../../includes/cub3d.h"

/*This function helps to find the max_width required for the normalize map*/
int max_width(char **map, int height)
{
    int i;
    int width;

    i = 0;
    width =0;
    while(i < height)
    {
        int len ;
        len = ft_strlen(map[i]);
        if(len > width)
            width = len;
        i++;
    }
    return(width);
}
int len_check_for_rect(char *line)
{
    if(!line)
        return(0);
    int len;
    len = ft_strlen(line);

    if(len > 0 && line[len -1] == ' ')
        len --;
    return(len);
}

int is_rectangular(char **map, int height, int expected_width)
{
    int i ;
    i =0;
    while ( i < height)
    {
        if(len_check_for_rect(map[i]) != expected_width)
            return(0);
        i++;
    }
    return(1);
}


char **normalize_map(char ** map,int height, int *out_width)
{
    char **new_map;
    int correct_width;
    correct_width = max_width(map,height);
    int i;
    int j;

    i =0;
    new_map = malloc(sizeof(char *) * (height + 1));
    if(!new_map)
        return(NULL);
    while(i < height)
    {
        new_map[i] = malloc(correct_width + 1 );
        if(!new_map[i])
        {
              free_2d_array(new_map);
              return(NULL);
        }
        j =0;
        while(map[i][j])
        {
            new_map[i][j] = map[i][j];
            j++;
        }
        while(j < correct_width)
            new_map[i][j++]  = ' ';
        new_map[i][correct_width] = '\0';
        i++;
    }
    new_map[height] = NULL;
    *out_width = correct_width;
    return (new_map);
}


