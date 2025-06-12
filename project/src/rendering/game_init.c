/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:52:11 by lgottsch          #+#    #+#             */
/*   Updated: 2025/06/12 21:37:03 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	assign_player_dir(t_game *game, int x, int y)
{
	if (game->map_r[y][x] == 'N')
	{
		game->player->dir_x = N_X;
		game->player->dir_y = N_Y;
	}
	else if (game->map_r[y][x] == 'S')
	{
		game->player->dir_x = S_X;
		game->player->dir_y = S_Y;
	}
	else if (game->map_r[y][x] == 'E')
	{
		game->player->dir_x = E_X;
		game->player->dir_y = E_Y;
	}
	else if (game->map_r[y][x] == 'W')
	{
		game->player->dir_x = W_X;
		game->player->dir_y = W_Y;
	}
}

void	init_player(t_game *game)
{
	int	y;
	int	x;

	game->player = (t_player *)malloc(sizeof(t_player));
	if (!game->player)
		free_everything(game, 1);
	ft_memset(game->player, '\0', sizeof(t_player));
	y = 0;
	while (y < game->map.map_height)
	{
		x = 0;
		while (x < game->map.map_width)
		{
			if (game->map_r[y][x] == 'N' || game->map_r[y][x] == 'S'
				|| game->map_r[y][x] == 'W' || game->map_r[y][x] == 'E')
			{
				game->player->pos_x = (double) x + 0.5;
				game->player->pos_y = (double) y + 0.5;
				assign_player_dir(game, x, y);
				break ;
			}
			x++;
		}
		y++;
	}
}

void	init_world(t_game *game)
{
	game->world = (t_world *)malloc(sizeof(t_world));
	if (!game->world)
		free_everything(game, 1);
	ft_memset(game->world, '\0', sizeof(t_world));
	game->world->color_ceiling = game->ceiling.full_color;
	game->world->color_floor = game->floor.full_color;
	load_no(game);
	load_so(game);
	load_we(game);
	load_ea(game);
}

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		free_everything(game, 1);
	game->image_p = NULL;
	game->image = (t_img_r *)malloc(sizeof(t_img_r));
	if (!game->image)
		free_everything(game, 1);
	ft_memset(game->image, '\0', sizeof(t_img_r));
	game->image->img = mlx_new_image(game->mlx, W_WIDTH, W_HEIGHT);
	if (!game->image->img)
		free_everything(game, 1);
	game->image->addr = mlx_get_data_addr(game->image->img,
			&game->image->bits_per_pixel, &game->image->line_length,
			&game->image->endian);
	if (!game->image->addr)
		free_everything(game, 1);
	game->window = mlx_new_window(game->mlx, W_WIDTH, W_HEIGHT, "CUB3D");
	if (!game->window)
		free_everything(game, 1);
}

void	init(t_game *game, bool *moved)
{
	init_mlx(game);
	game->moved = moved;
	game->map_r = game->map.map;
	init_player(game);
	init_world(game);
}
