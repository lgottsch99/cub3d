/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_extension_valid.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-10 08:58:46 by selango           #+#    #+#             */
/*   Updated: 2025-06-10 08:58:46 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cub3d.h"
#include "../../includes/cub3d.h"

int valid_cub_ext(char *path)
{
    int len ;
    len = ft_strlen(path);
    if(!len || len < 4)
        return(0);
    return(ft_strcmp(path + len - 4, ".cub") == 0);
}

int is_valid_char(char c)
{
    return(c == '0' || c == 'N' || c == 'S'
            || c == 'W' || c == 'E'|| c =='1' || c == ' ');
}