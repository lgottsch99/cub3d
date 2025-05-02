/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:10:57 by lgottsch          #+#    #+#             */
/*   Updated: 2025/05/02 14:09:33 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
approach:

	render one image of simple scene 

	add texture
	
	add movement


*/

#include "../includes/cub3d.h"

void	init_test_player(t_game *game)
{
	printf("in init test player\n");

	//malloc player struct
	game->player = (t_player *)malloc(sizeof(t_player));
	//if (!game->player)
		//free

	game->player->pos_x = 3;
	game->player->pos_x = 4;
	
}

void	init_test_map(t_game *game)
{
	printf("in init test map\n");
	
	char *test_map[] = {
		"111111", //row 0
		"100101",
		"101001",
		"1100N1", //row 3 //player at 3,4
		"111111"
	};

	game->map = test_map;

	// printf("char at pos 1 1: %c\n", game->map[1][1]);
	// printf("char at pos 3 3: %c\n", game->map[3][3]);
}

void	init_test_world(t_game *game)
{
	game->world = (t_world *)malloc(sizeof(t_world));
	//if(!game->world)
		//free

	game->world->floor_r = 11;
	game->world->floor_g = 173;
	game->world->floor_b = 7;

	game->world->ceiling_r = 84;
	game->world->ceiling_g = 117;
	game->world->ceiling_b = 143;


}

static void	init(t_game *game)
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

	init_test_map(game);
	init_test_player(game);
	init_test_world(game);


}

void	raycast(t_game *game)
{
	//0 init basics
	init(game);
	//printf("after init raycast\n");

	//draw floor and ceiling



	if (game->mlx)
		mlx_loop(game->mlx); //keeping window open
}
