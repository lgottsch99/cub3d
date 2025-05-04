/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:11:44 by lgottsch          #+#    #+#             */
/*   Updated: 2025/05/04 16:29:27 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Ft calculating length of vector
for double : sqrt()
for float : sgrtf()
*/
float	vector_len(float x, float y)
{
	return(sqrtf((x * x) + (y * y)));
}


/* function drawing vertical line (wall)
*/
void	draw_wall_line(t_game *game, int vertical_row, int draw_start, int draw_end, int color)
{
	printf("in draw vertical line\n");
	int i;

	i = 0;
	while(i < W_HEIGHT)
	{
		if (i >= draw_start && i <= draw_end)
		{
			//printf("putting pixel\n");
			my_mlx_pixel_put(game->image, i, vertical_row, color);
		}
		i++;
	}
}