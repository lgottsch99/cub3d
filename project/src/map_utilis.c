/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utilis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-05 11:04:03 by selango           #+#    #+#             */
/*   Updated: 2025-05-05 11:04:03 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	exit_error(char *str)
{
	printf("Error:%s\n", str);
	exit(EXIT_FAILURE);
}

int str_digit(char *str)
{
	int i ;
	i = 0;
	if(!str)
		return 0;
	while (str[i])
	{
		if(!ft_isdigit(str[i]))
			return 0;
		i++;
	}
	return (1);
}
void free_2d_array(char **strs)
{
	while(*strs)
	{
		free(*strs);
		*strs++;
	}
}