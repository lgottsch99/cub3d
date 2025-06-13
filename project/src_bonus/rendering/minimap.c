/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:52:47 by lgottsch          #+#    #+#             */
/*   Updated: 2025/06/12 21:27:19 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_square(t_minimapsquare *ms, int square_size,
	t_game *game, int color)
{
	t_minisquare	m;

	m.start_x = ms->x * square_size;
	m.start_y = ms->y * square_size;
	m.current_x = m.start_x;
	m.current_y = m.start_y;
	m.a = 0;
	while (m.a < square_size)
	{
		m.b = 0;
		m.current_y = m.start_y;
		while (m.b < square_size)
		{
			my_mlx_pixel_put(game->image, m.current_x, m.current_y, color);
			m.current_y++;
			m.b++;
		}
		my_mlx_pixel_put(game->image, m.current_x, m.current_y, color);
		m.current_x++;
		m.a++;
	}
}

void	draw_map_squares(t_game *game, int square_size,
	int map_height, int map_width)
{
	t_minimapsquare	ms;

	ms.square_color_wall = create_color(0, 255, 255, 0);
	ms.square_color_floor = create_color(0, 237, 237, 200);
	ms.x = 0;
	while (ms.x < map_height)
	{
		ms.y = 0;
		while (ms.y < map_width)
		{
			if (get_map_point(ms.x, ms.y, game) == 1)
				draw_square(&ms, square_size, game, ms.square_color_wall);
			else if (get_map_point(ms.x, ms.y, game) == 0)
				draw_square(&ms, square_size, game, ms.square_color_floor);
			ms.y++;
		}
		ms.x++;
	}
}

void	draw_player(t_game *game, int square_size,
	int player_color, int player_size)
{
	int	i;
	int	a;
	int	x;
	int	y;

	x = game->player->pos_x * square_size;
	y = game->player->pos_y * square_size;
	i = 0;
	while (i < player_size)
	{
		y = game->player->pos_y * square_size;
		a = 0;
		while (a < player_size)
		{
			my_mlx_pixel_put(game->image, y, x, player_color);
			y++;
			a++;
		}
		x++;
		i++;
	}
}

void	minimap(t_game *game)
{
	int	square_size;
	int	player_color;
	int	player_size;

	player_color = create_color(0, 0, 0, 0);
	player_size = 5;
	square_size = calc_square_size(game->map.map_height, game->map.map_width);
	if (square_size == 0)
		return ;
	draw_map_squares(game, square_size, game->map.map_height,
		game->map.map_width);
	draw_player(game, square_size, player_color, player_size);
}
