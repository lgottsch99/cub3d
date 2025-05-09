/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Watanudon <Watanudon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:11:44 by lgottsch          #+#    #+#             */
/*   Updated: 2025/05/06 13:22:56 by Watanudon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


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