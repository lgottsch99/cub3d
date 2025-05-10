/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Watanudon <Watanudon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:11:44 by lgottsch          #+#    #+#             */
/*   Updated: 2025/05/10 11:33:55 by Watanudon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


/* function drawing vertical line (wall)
*/
void	draw_wall_line(t_game *game, int vertical_row, int draw_start, int draw_end, int color)
{
	printf("in draw vertical line\n");
	int i;
	int color_ceiling;
	int color_floor;
	
	color_ceiling = create_color(0, game->world->ceiling_r, game->world->ceiling_g, game->world->ceiling_b);
	color_floor = create_color(0, game->world->floor_r, game->world->floor_g, game->world->floor_b);
	i = 0;
	while(i < W_HEIGHT)
	{
		if (i >= 0 && i < draw_start)
		{
			my_mlx_pixel_put(game->image, i, vertical_row, color_ceiling);
		}
		if (i >= draw_start && i <= draw_end)
		{
			//printf("putting pixel\n");
			my_mlx_pixel_put(game->image, i, vertical_row, color);
		}
		if (i > draw_end)
			my_mlx_pixel_put(game->image, i, vertical_row, color_floor);
		i++;
	}
}