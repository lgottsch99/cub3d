/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Watanudon <Watanudon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:10:57 by lgottsch          #+#    #+#             */
/*   Updated: 2025/05/03 18:55:30 by Watanudon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
approach:
	do 2d minimap first 

	render one image of simple scene 
	add texture
	add movement

???:
	ho wto get FOV vector/ vectors from player thru it
*/

#include "../includes/cub3d.h"

void	init_test_player(t_game *game)
{
	printf("in init test player\n");

	//malloc player struct
	game->player = (t_player *)malloc(sizeof(t_player));
	//if (!game->player)
		//free

	game->player->pos_x = 4;
	game->player->pos_y = 4;
	
}

void	init_test_map(t_game *game)
{
	printf("in init test map\n");
	
	static char *test_map[] = {
		"111111", //row 0
		"100101",
		"101001",
		"1100N1", //row 3 //player at 3,4
		"100001",
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


void	draw_floor_ceiling(t_game *game)
{
	printf("in draw floor and ceiling\n");
	int	i;
	int y;
	int color;

	i = 0;
	while (i < W_WIDTH)
	{
		y = 0;
		while (y < W_HEIGHT / 2) //ceiling OK
		{
			printf("drawing ceiling\n");
			color = create_color(0, game->world->ceiling_r, game->world->ceiling_g, game->world->ceiling_b);
			my_mlx_pixel_put(game->image, y, i, color);
			y++;
		}
		while (y < W_HEIGHT) //floor
		{
			printf("drawing floor\n");

			color = create_color(0, game->world->floor_r, game->world->floor_g, game->world->floor_b);
			my_mlx_pixel_put(game->image, y, i, color);
			y++;
		}
		i++;
	}
}

void	raycast(t_game *game) //for now: lillis main
{
	//0 init basics
	init(game);
	//draw floor and ceiling
	//draw_floor_ceiling(game); //OK

	//minimap for understanding what is going on (movement)
	minimap(game);

	//actual raycasting
		//get player pos and dir vector -> camera plane vector
		//lets say if N looking north: direction: x = 0, y = +1
		//calc camera plane end points ->player pos to endpoints = outer most edges of fov/img
		//divide distance into W_Width, for each pixel:
			//calc vector from player to next wall hit
			//calc vector distance , get height (and direction etc) of wall line to draw












	
	//hooks();


	mlx_put_image_to_window(game->mlx, game->window, game->image->img, 0, 0);
	if (game->mlx)
		mlx_loop(game->mlx); //keeping window open
}
