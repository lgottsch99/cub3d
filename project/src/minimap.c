
#include "../includes/cub3d.h"

void	draw_square(int x, int y, int square_size, t_game *game)
{
	//go to start point point x y is start point from there 
	int start_x;
	int start_y;
	int a;
	int current_x;
	int current_y;
	int color = create_color(100, 255, 255, 0);

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


void	draw_map_squares(t_game *game, int square_size)//TODO
{
	int x;
	int y;

	int map_width = 6; //TODO make dynamic later 
	int map_height = 6;

	x = 0;
	while (x < map_height)
	{
		y = 0;
		while (y < map_width)
		{
			//get point in map
			if (get_map_point(x, y, game) == 1)			
				draw_square(x, y, square_size, game);
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
	int square_size = 20; //size in pixel

	//draw square for each 1 in map
		//go thru map
	draw_map_squares(game, square_size);

	//draw player 
	draw_player(game, square_size);

	//add hooks and see if moving is correct


}