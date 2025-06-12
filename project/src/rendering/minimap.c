/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:52:47 by lgottsch          #+#    #+#             */
/*   Updated: 2025/06/12 17:10:45 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub3d.h"

void	draw_square(int x, int y, int square_size, t_game *game, int color)
{
	//go to start point point x y is start point from there 
	int start_x;
	int start_y;
	int a;
	int current_x;
	int current_y;

	start_x = x * square_size;
	start_y = y * square_size;

	current_x = start_x;
	current_y = start_y;
	a = 0;
	while (a < square_size) //top line to right
	{
		int b = 0;
		current_y = start_y;
		while (b < square_size)
		{
			my_mlx_pixel_put(game->image, current_x, current_y, color);
			current_y++;
			b++;
		}
		//printf("drawing square line top\n");
		my_mlx_pixel_put(game->image, current_x, current_y, color);
		//current_y++;
		current_x++;
		a++;
	}
}


void	draw_map_squares(t_game *game, int square_size, int map_height, int map_width)//TODO match map in file von richtungen her
{
	int x;
	int y;
	int	square_color_wall;
	int	square_color_floor;


	square_color_wall = create_color(0, 255, 255, 0);
	square_color_floor = create_color(0, 237, 237, 200);

	x = 0;
	while (x < map_height)
	{
		y = 0;
		while (y < map_width)
		{
			//get point in map
			if (get_map_point(x, y, game) == 1)			
				draw_square(x, y, square_size, game, square_color_wall);
			else if (get_map_point(x, y, game) == 0)
				draw_square(x, y, square_size, game, square_color_floor);
			y++;
		}
		x++;
	}
}


void	draw_player(t_game *game, int square_size)
{
	//printf("srawing player\n");
	int	i;
	int a;
	int player_size = 5; //player size in px
	int x;
	int y; 
	int color = create_color(0, 0, 0, 0);

	x = game->player->pos_x * square_size;
	y = game->player->pos_y * square_size;

	i = 0;
	while (i < player_size)
	{
		y = game->player->pos_y * square_size;
		a = 0;
		while (a < player_size)
		{
			my_mlx_pixel_put(game->image, y, x, color);
			y++;
			a++;
		}
		x++;
		i++;
	}
}

void	minimap(t_game *game) //maybe put some buffer around map and not start drawing at 0,0?
{
	int square_size; //size in pixel
	int map_width; //TODO make dynamic later 
	int map_height;

	//get map size
	map_width = count_map(game->map_r, 1); //1 for width
	map_height = count_map(game->map_r, 2); //2 for height
	printf("Minimap map width: %i\n", map_width);
	printf("Minimap map hieght: %i\n", map_height);

	//calc square size minimap
	//make height not more than 1/3 of window height
	square_size = calc_square_size(map_height, map_width);
	if (square_size == 0)
		return;
	//draw square for each 1 in map
		//go thru map
	draw_map_squares(game, square_size, map_height, map_width);

	//draw player 
	draw_player(game, square_size);
}