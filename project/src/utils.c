/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:10:00 by lgottsch          #+#    #+#             */
/*   Updated: 2025/05/04 17:58:39 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
Function to color single pixel at x/y in image to color
*/
void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (x * data->line_length + y * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}


//creates single integer representing color value (0 nothing, 255 full)
int	create_color(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/* Function to get the content of a point at x/y in map.
	Returns 1 if point is wall, 
	0 if not
*/
int get_map_point(int x, int y, t_game *game)
{
	//get specific char at [x] [y]
	char content;

	//go to str in x dir
	content = game->map[x][y];
	//printf("map at x %i y %i: %c\n", x, y, content);
	if (content == '1')
		return (1);
	else
		return (0);
}
