/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:10:00 by lgottsch          #+#    #+#             */
/*   Updated: 2025/06/12 20:46:34 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
Function to color single pixel at x/y in image to color
*/
void	my_mlx_pixel_put(t_img_r *data, int x, int y, int color)
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
int	get_map_point(int x, int y, t_game *game)
{
	char	content;

	content = game->map_r[x][y];
	if (content == '1')
		return (1);
	else if (content == '0' || content == 'N'
		|| content == 'S' || content == 'W')
		return (0);
	else
		return (-1);
}

/* Ft that clears img buffer of any colors drawn. 
Only needed when continously rendering imgs 
*/
void	clear_image(t_game *game)
{
	int	i;
	int	y;
	int	color;

	color = create_color(0, 0, 0, 0);
	i = 0;
	while (i < W_HEIGHT)
	{
		y = 0;
		while (y < W_WIDTH)
		{
			my_mlx_pixel_put(game->image, i, y, color);
			y++;
		}
		i++;
	}
}
