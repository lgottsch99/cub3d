/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:52:26 by lgottsch          #+#    #+#             */
/*   Updated: 2025/05/17 15:11:13 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub3d.h"


int count_map(char **map, int mode)
{
	int	i;

	if (mode == 1)
	{
		i = 0;
		while (map[0][i])
			i++;
	}
	else
	{
		i = 0;
		while (map[i])
			i++;
	}
	return (i);
}

int	calc_square_size(int map_height, int map_width)
{
	int square_size;
	(void) map_width;

	square_size = 18; //default size
	while ((map_height * square_size) > (0.3 * W_HEIGHT))
		square_size--;
	
	if ((map_width * square_size) > (0.4 * W_WIDTH))
	{
		while ((map_width * square_size) > (0.4 * W_WIDTH))
			square_size--;
	}

	if (square_size == 0) //if map very big
	{
		square_size = 1;
		if ((map_width * square_size) > W_WIDTH || (map_height * square_size) > W_HEIGHT)
		{
			printf("ERROR MINIMAP: game map to big to be shown on window\n");
			return (0);
		}
	}
	
	
	return (square_size);
}

