/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:52:11 by lgottsch          #+#    #+#             */
/*   Updated: 2025/06/12 19:53:28 by lgottsch         ###   ########.fr       */
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

void	init_player(t_game *game) //TODO parse player pos
{
	//malloc player struct
	game->player = (t_player *)malloc(sizeof(t_player));
	// if (!game->player)
		//free

	int y;
	int x;
	
	y = 0;
	while (y < game->map.map_height)
	{
		x = 0;
		while (x < game->map.map_width)
		{
			if (game->map_r[y][x] == 'N' || game->map_r[y][x] == 'S' || game->map_r[y][x] == 'W' || game->map_r[y][x] == 'E')
			{
				game->player->pos_x = (double) x + 0.5;
				game->player->pos_y = (double) y + 0.5;
				assign_player_dir(game, x, y);
				break;
			}
			x++;
		}
		y++;
	}

	//starting position based on map coords (spawn player in middle of tile)
	// game->player->pos_x = 3.5;
	// game->player->pos_y = 4.5;

	//starting orientation based on char N E S W //TODO
	// game->player->dir_x = N_X;
	// game->player->dir_y = N_Y;

	// game->player->dir_x = S_X;
	// game->player->dir_y = S_Y;

	// game->player->dir_x = E_X;
	// game->player->dir_y = E_Y;

	// game->player->dir_x = W_X;
	// game->player->dir_y = W_Y;

}



void	init_world(t_game *game)
{
	game->world = (t_world *)malloc(sizeof(t_world));
	//if(!game->world)
		//free

	game->world->color_ceiling = game->ceiling.full_color; //create_color(0, game->world->ceiling_r, game->world->ceiling_g, game->world->ceiling_b);
	game->world->color_floor = game->floor.full_color;//create_color(0, game->world->floor_r, game->world->floor_g, game->world->floor_b);

	//LOAD TEXTURES	
	game->world->tex_NO.relative_path = game->No_texture.path; //"../Textures_xpm/Planet1.xpm";
	game->world->tex_NO.img = mlx_xpm_file_to_image(game->mlx, game->world->tex_NO.relative_path, &game->world->tex_NO.tex_width, &game->world->tex_NO.tex_height);
	if (game->world->tex_NO.img == NULL)
		printf("LOADING NO TEXTURE FAILED\n");
	game->world->tex_NO.data_addr = mlx_get_data_addr(game->world->tex_NO.img, &game->world->tex_NO.bpp, &game->world->tex_NO.size_line, &game->world->tex_NO.endian);
	if (game->world->tex_NO.data_addr == NULL)
		printf("getting NO TEXTURE addr FAILED\n");
	// 	free
	// printf("texture width: %i\n", game->world->tex_NO.tex_width);
	// printf("texture height: %i\n", game->world->tex_NO.tex_height);

	game->world->tex_SO.relative_path = game->So_texture.path; // "../Textures_xpm/Planet2.xpm";
	game->world->tex_SO.img = mlx_xpm_file_to_image(game->mlx, game->world->tex_SO.relative_path, &game->world->tex_SO.tex_width, &game->world->tex_SO.tex_height);
	if (game->world->tex_SO.img == NULL)
		printf("LOADING SO TEXTURE FAILED\n");
	game->world->tex_SO.data_addr = mlx_get_data_addr(game->world->tex_SO.img, &game->world->tex_SO.bpp, &game->world->tex_SO.size_line, &game->world->tex_SO.endian);
	if (game->world->tex_SO.data_addr == NULL)
		printf("getting SO TEXTURE addr FAILED\n");


	game->world->tex_WE.relative_path = game->We_texture.path;//"../Textures_xpm/Planet3.xpm";
	game->world->tex_WE.img = mlx_xpm_file_to_image(game->mlx, game->world->tex_WE.relative_path, &game->world->tex_WE.tex_width, &game->world->tex_WE.tex_height);
	if (game->world->tex_WE.img == NULL)
		printf("LOADING WE TEXTURE FAILED\n");
	game->world->tex_WE.data_addr = mlx_get_data_addr(game->world->tex_WE.img, &game->world->tex_WE.bpp, &game->world->tex_WE.size_line, &game->world->tex_WE.endian);
	if (game->world->tex_WE.data_addr == NULL)
		printf("getting WE TEXTURE addr FAILED\n");


	game->world->tex_EA.relative_path = game->Ea_texture.path; //"../Textures_xpm/Planet4.xpm";
	game->world->tex_EA.img = mlx_xpm_file_to_image(game->mlx, game->world->tex_EA.relative_path, &game->world->tex_EA.tex_width, &game->world->tex_EA.tex_height);
	if (game->world->tex_EA.img == NULL)
		printf("LOADING EA TEXTURE FAILED\n");
	game->world->tex_EA.data_addr = mlx_get_data_addr(game->world->tex_EA.img, &game->world->tex_EA.bpp, &game->world->tex_EA.size_line, &game->world->tex_EA.endian);
	if (game->world->tex_EA.data_addr == NULL)
		printf("getting EA TEXTURE addr FAILED\n");


}


void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		free_everything(game, 1);
	game->image = (t_img_r*)malloc(sizeof(t_img_r));
	if (!game->image)
		free_everything(game, 1);
	game->image->img = mlx_new_image(game->mlx, W_WIDTH, W_HEIGHT); //init img
	if (!game->image->img)
		free_everything(game, 1);
	game->image->addr = mlx_get_data_addr(game->image->img, &game->image->bits_per_pixel, &game->image->line_length, &game->image->endian);
	if (!game->image->addr)
		free_everything(game, 1);
	game->window = mlx_new_window(game->mlx, W_WIDTH, W_HEIGHT, "CUB3D"); //init window
	if(!game->window)
		free_everything(game, 1);
}

void	init(t_game *game, bool *moved)
{
	init_mlx(game);
	// game->mlx = mlx_init();
	// if (!game->mlx)
	// 	free_everything(game, 1);
	// game->image = (t_img_r*)malloc(sizeof(t_img_r));
	// if (!game->image)
	// 	free_everything(game, 1);
	// game->image->img = mlx_new_image(game->mlx, W_WIDTH, W_HEIGHT); //init img
	// if (!game->image->img)
	// 	free_everything(game, 1);
	// game->image->addr = mlx_get_data_addr(game->image->img, &game->image->bits_per_pixel, &game->image->line_length, &game->image->endian);
	// if (!game->image->addr)
	// 	free_everything(game, 1);
	// game->window = mlx_new_window(game->mlx, W_WIDTH, W_HEIGHT, "CUB3D"); //init window
	// if(!game->window)
	// 	free_everything(game, 1);
	game->moved = moved;
	game->map_r = game->map.map;
	init_player(game);
	init_world(game);
}
