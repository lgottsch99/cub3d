/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:52:11 by lgottsch          #+#    #+#             */
/*   Updated: 2025/05/17 15:11:02 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


void	init_test_player(t_game *game) //DEVELOPING ONLY
{
	printf("in init test player\n");

	//malloc player struct
	game->player = (t_player *)malloc(sizeof(t_player));
	//if (!game->player)
		//free

	//starting position based on map coords (spawn player in middle of tile)
	game->player->pos_x = 3.5;
	game->player->pos_y = 4.5;

	//starting orientation based on char N E S W //TODO
	// game->player->dir_x = N_X;
	// game->player->dir_y = N_Y;

	// game->player->dir_x = S_X;
	// game->player->dir_y = S_Y;

	game->player->dir_x = E_X;
	game->player->dir_y = E_Y;

	// game->player->dir_x = W_X;
	// game->player->dir_y = W_Y;

}

void	init_test_map(t_game *game) //DEVELOPING ONLY
{
	printf("in init test map\n");
	
	static char *test_map[] = {
		"1111111111", //row y = 0
		"1000000001",
		"1001000101",
		"1010001001", //row y = 3 
		"100N001111", //player at x3 y4
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1111111111"
	};

	game->map = test_map;

	// printf("char at pos 1 1: %c\n", game->map[1][1]);
	// printf("char at pos 3 3: %c\n", game->map[3][3]);
}

void	init_test_world(t_game *game) //DEVELOPING ONLY
{
	game->world = (t_world *)malloc(sizeof(t_world));
	//if(!game->world)
		//free

	game->world->floor_r = 168; //sandy brown
	game->world->floor_g = 100;
	game->world->floor_b = 5;

	game->world->ceiling_r = 0; //dark blue
	game->world->ceiling_g = 5;
	game->world->ceiling_b = 138;


	game->world->color_ceiling = create_color(0, game->world->ceiling_r, game->world->ceiling_g, game->world->ceiling_b);
	game->world->color_floor = create_color(0, game->world->floor_r, game->world->floor_g, game->world->floor_b);

	//LOAD TEXTURES
	//game->world->tex_NO.relative_path = "../Textures_png/Planet3.png";
		// ! mlx_png_file_to_image officially leaks mem
	//game->world->tex_NO.img = mlx_png_file_to_image(game->mlx, game->world->tex_NO.relative_path, &game->world->tex_NO.tex_width, &game->world->tex_NO.tex_height);
	game->world->tex_NO.relative_path = "../Textures_xpm/Planet1.xpm";
	game->world->tex_NO.img = mlx_xpm_file_to_image(game->mlx, game->world->tex_NO.relative_path, &game->world->tex_NO.tex_width, &game->world->tex_NO.tex_height);
	if (game->world->tex_NO.img == NULL)
		printf("LOADING NO TEXTURE FAILED\n");
	game->world->tex_NO.data_addr = mlx_get_data_addr(game->world->tex_NO.img, &game->world->tex_NO.bpp, &game->world->tex_NO.size_line, &game->world->tex_NO.endian);
	if (game->world->tex_NO.data_addr == NULL)
		printf("getting NO TEXTURE addr FAILED\n");
	// 	free
	// printf("texture width: %i\n", game->world->tex_NO.tex_width);
	// printf("texture height: %i\n", game->world->tex_NO.tex_height);

	game->world->tex_SO.relative_path = "../Textures_xpm/Planet2.xpm";
	game->world->tex_SO.img = mlx_xpm_file_to_image(game->mlx, game->world->tex_SO.relative_path, &game->world->tex_SO.tex_width, &game->world->tex_SO.tex_height);
	if (game->world->tex_SO.img == NULL)
		printf("LOADING SO TEXTURE FAILED\n");
	game->world->tex_SO.data_addr = mlx_get_data_addr(game->world->tex_SO.img, &game->world->tex_SO.bpp, &game->world->tex_SO.size_line, &game->world->tex_SO.endian);
	if (game->world->tex_SO.data_addr == NULL)
		printf("getting SO TEXTURE addr FAILED\n");


	game->world->tex_WE.relative_path = "../Textures_xpm/Planet3.xpm";
	game->world->tex_WE.img = mlx_xpm_file_to_image(game->mlx, game->world->tex_WE.relative_path, &game->world->tex_WE.tex_width, &game->world->tex_WE.tex_height);
	if (game->world->tex_WE.img == NULL)
		printf("LOADING WE TEXTURE FAILED\n");
	game->world->tex_WE.data_addr = mlx_get_data_addr(game->world->tex_WE.img, &game->world->tex_WE.bpp, &game->world->tex_WE.size_line, &game->world->tex_WE.endian);
	if (game->world->tex_WE.data_addr == NULL)
		printf("getting WE TEXTURE addr FAILED\n");


	game->world->tex_EA.relative_path = "../Textures_xpm/Planet4.xpm";
	game->world->tex_EA.img = mlx_xpm_file_to_image(game->mlx, game->world->tex_EA.relative_path, &game->world->tex_EA.tex_width, &game->world->tex_EA.tex_height);
	if (game->world->tex_EA.img == NULL)
		printf("LOADING EA TEXTURE FAILED\n");
	game->world->tex_EA.data_addr = mlx_get_data_addr(game->world->tex_EA.img, &game->world->tex_EA.bpp, &game->world->tex_EA.size_line, &game->world->tex_EA.endian);
	if (game->world->tex_EA.data_addr == NULL)
		printf("getting EA TEXTURE addr FAILED\n");


}

void	init(t_game *game, bool *moved)
{
	game->mlx = mlx_init(); //init mlx
	if (!game->mlx)
		exit(1);
	game->image = (t_img*)malloc(sizeof(t_img)); //malloc space for img
	//if (!game->image)
		//free
	game->image->img = mlx_new_image(game->mlx, W_WIDTH, W_HEIGHT); //init img
	//if (!game->image->img)
		//free
	game->image->addr = mlx_get_data_addr(game->image->img, &game->image->bits_per_pixel, &game->image->line_length, &game->image->endian);
	//if (!game->image->addr)
		//free
	game->window = mlx_new_window(game->mlx, W_WIDTH, W_HEIGHT, "CUB3D"); //init window
	//if(!game->window)
		//free
	game->moved = moved;

	init_test_map(game);
	init_test_player(game);
	init_test_world(game);

}
