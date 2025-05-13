/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Watanudon <Watanudon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:10:57 by lgottsch          #+#    #+#             */
/*   Updated: 2025/05/13 10:47:57 by Watanudon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
approach:
	add textures
		load textures:
		at init store textures in some buffer, The buffer will be an array of integers, where each integer represents the colour of a pixel
	for each ray: 
		calc x coord of WHERE it hits the wall in coord grid -> same x coord 

TODO
	boundary check more complete
	movement smooth?

	freeing

	minimap dynamic


???:
	
*/

#include "../includes/cub3d.h"
# include "../lib/mlx_mac/mlx.h" //minilibx for graphics rendering


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

	game->world->floor_r = 150;
	game->world->floor_g = 168;
	game->world->floor_b = 150;

	game->world->ceiling_r = 207;
	game->world->ceiling_g = 255;
	game->world->ceiling_b = 252;

	//LOAD TEXTURES
	game->world->tex_NO.relative_path = "./Sand1.png";
		// ! mlx_png_file_to_image officially leaks mem
	game->world->tex_NO.img = mlx_png_file_to_image(game->mlx, game->world->tex_NO.relative_path, &game->world->tex_NO.tex_width, &game->world->tex_NO.tex_height);
	if (game->world->tex_NO.img == NULL)
		printf("LOADING NO TEXTURE FAILED\n");
	game->world->tex_NO.data_addr = mlx_get_data_addr(game->world->tex_NO.img, &game->world->tex_NO.bpp, &game->world->tex_NO.size_line, &game->world->tex_NO.endian);
	if (game->world->tex_NO.data_addr == NULL)
		printf("getting NO TEXTURE addr FAILED\n");
	// 	free
	// printf("texture width: %i\n", game->world->tex_NO.tex_width);
	// printf("texture height: %i\n", game->world->tex_NO.tex_height);

	game->world->tex_SO.relative_path = "./Planet1.png";
	game->world->tex_SO.img = mlx_png_file_to_image(game->mlx, game->world->tex_SO.relative_path, &game->world->tex_SO.tex_width, &game->world->tex_SO.tex_height);
	if (game->world->tex_SO.img == NULL)
		printf("LOADING SO TEXTURE FAILED\n");
	game->world->tex_SO.data_addr = mlx_get_data_addr(game->world->tex_SO.img, &game->world->tex_SO.bpp, &game->world->tex_SO.size_line, &game->world->tex_SO.endian);
	if (game->world->tex_SO.data_addr == NULL)
		printf("getting SO TEXTURE addr FAILED\n");


	game->world->tex_WE.relative_path = "./Planet2.png";
	game->world->tex_WE.img = mlx_png_file_to_image(game->mlx, game->world->tex_WE.relative_path, &game->world->tex_WE.tex_width, &game->world->tex_WE.tex_height);
	if (game->world->tex_WE.img == NULL)
		printf("LOADING WE TEXTURE FAILED\n");
	game->world->tex_WE.data_addr = mlx_get_data_addr(game->world->tex_WE.img, &game->world->tex_WE.bpp, &game->world->tex_WE.size_line, &game->world->tex_WE.endian);
	if (game->world->tex_WE.data_addr == NULL)
		printf("getting WE TEXTURE addr FAILED\n");


	game->world->tex_EA.relative_path = "./Wasser.png";
	game->world->tex_EA.img = mlx_png_file_to_image(game->mlx, game->world->tex_EA.relative_path, &game->world->tex_EA.tex_width, &game->world->tex_EA.tex_height);
	if (game->world->tex_EA.img == NULL)
		printf("LOADING EA TEXTURE FAILED\n");
	game->world->tex_EA.data_addr = mlx_get_data_addr(game->world->tex_EA.img, &game->world->tex_EA.bpp, &game->world->tex_EA.size_line, &game->world->tex_EA.endian);
	if (game->world->tex_EA.data_addr == NULL)
		printf("getting EA TEXTURE addr FAILED\n");


}

static void	init(t_game *game, bool *moved)
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



/* Ft that clears img buffer of any colors drawn. Only needed when continously rendering imgs 
*/
void	clear_image(t_game *game) 
{
	printf("clearing image\n");
	int	i;
	int y;
	int color;

	color = create_color(0, 0, 0, 0);
	i = 0;
	while(i < W_HEIGHT)
	{
		//printf("clearing image - outer loop\n");
		y = 0;
		while (y < W_WIDTH)
		{
			//printf("clearing image - inner loop\n");

			my_mlx_pixel_put(game->image, i, y, color);
			y++;
		}
		i++;
	}
}


void	raycast(t_game *game)
{
	double plane_len;
	int	i;

	//actual raycasting
		//get player pos and dir vector -> camera plane vector
		//calc camera plane end points ->player pos to endpoints = outer most edges of fov/img
		//divide distance into W_Width, for each pixel:
			//calc vector from player to next wall hit
			//calc vector distance , get height (and direction etc) of wall line to draw

	//dir + pos vector already set (but need to put dir at correct location: pos + dir)

	//calc len + dir of plane to match FOV
	plane_len = tan((FOV * M_PI /180.0) / 2.0); //tan() expects radians!!!
	printf("plane len: %f\n", plane_len);

	//get plane vector
	game->player->plane_x = (-1.0 * game->player->dir_y) * plane_len;
	game->player->plane_y = game->player->dir_x * plane_len;
	printf("plane vector x: %f y: %f\n", game->player->plane_x, game->player->plane_y);


//raycasting loop () to render single scene
	//i = 100;
	i = 0;
	while (i < W_WIDTH) //for each vertical line (= each i in width of window)
	{
		//printf("Player pos: (%f, %f)\n", game->player->pos_x, game->player->pos_y);

		double raydir_x;
		double raydir_y;
		//each ray is sum of player pos + dir =/- part of plane (camera x?multiplier of plane len)
		double len; //multiplier for current i location in window -> length of plane vector

		len = (2 * i) / (double)W_WIDTH - 1;
		raydir_x = game->player->dir_x + game->player->plane_x * len;
		raydir_y = game->player->dir_y + game->player->plane_y * len;
		printf("direction of ray x: %f y: %f\n", raydir_x, raydir_y);

	//dda setup
		printf("setting up dda vars\n");
		//which box of map are we in
		int map_x = (int) game->player->pos_x; 
		int map_y = (int) game->player->pos_y;
		printf("in box x: %i y: %i\n", map_x, map_y);

		//len of ray from current pos to next x or y side
		double sidedist_x;
		double sidedist_y;

		//length the ray must travel to move from one x-side (vertical line) to the next, or one y-side (horizontal line) to the next
		double	delta_dist_x;
		if (raydir_x == 0)
			delta_dist_x = 1e30; //huge num to avoid div/0
		else
			delta_dist_x = (double) fabs(1 / raydir_x);

		double	delta_dist_y;
		if (raydir_y == 0)
			delta_dist_y = 1e30; //huge num to avoid div/0 9so big that line will never cross that axis)
		else
			delta_dist_y = (double) fabs(1 / raydir_y);

		double wall_distance; //later used to render line

		int step_x; //=1 or -1 depending on direction of ray thru grid
		int step_y;

		int hit = 0; //stop once wallhit
		int side; //wall on x or y side of grid?

	//calc first stepX, stepY, and the initial sideDistX and sideDistY before dda can start
		if (raydir_x < 0)
		{
			step_x = -1;
			//distance from the ray starting position to the first side to the left
			sidedist_x = (game->player->pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			//the first side to the right is used instead
			sidedist_x = (map_x + 1.0 - game->player->pos_x) * delta_dist_x;
		}

		if (raydir_y < 0)
		{
			step_y = -1;
			sidedist_y = (game->player->pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			sidedist_y = (map_y + 1.0 - game->player->pos_y) * delta_dist_y;
		}
		
	//dda loop
		printf("going into dda loop\n");

		while (hit == 0)
		{
			printf("in dda loop\n");

			//jump to next map square. either in x or y direction
			if (sidedist_x < sidedist_y)
			{
				sidedist_x += delta_dist_x;
				map_x += step_x;
				side = 0; //side on x line
			}
			else
			{
				sidedist_y += delta_dist_y;
				map_y += step_y;
				side = 1; //side on y line
			}
			//check if wallhit
			if (game->map[map_y][map_x] == '1')
				hit = 1;
		}

	//calc distance of ray to wall
		// if (side == 0)//x grid line
		// 	wall_distance = (sidedist_x - delta_dist_x);
		// else
		// 	wall_distance = (sidedist_y - delta_dist_y);

		// if (wall_distance == 0)
		// 	printf("Warning: wall_distance = 0 at column %d (side = %d, raydir_x = %f, raydir_y = %f)\n", i, side, raydir_x, raydir_y);
		if (side == 0)
			wall_distance = (map_x - game->player->pos_x + (1 - step_x) / 2) / raydir_x;
		else
			wall_distance = (map_y - game->player->pos_y + (1 - step_y) / 2) / raydir_y;

		printf("WALL DIST: %f\n", wall_distance);
	//calc height of line to draw
		double line_height = 0;
		//int h = 7; //multiplier to make walls higher/lower,

		line_height = (int)(W_HEIGHT / wall_distance);
		printf("LINE HEIGHT: %f\n", line_height);

		if (line_height < 5)
			line_height = 5;
		
		//calc highest and lowest pixel to draw in RENDERED IMG
		int draw_start;
		draw_start = (W_HEIGHT - line_height) / 2;
		if (draw_start < 0)
			draw_start = 0;

		int draw_end;
		draw_end = draw_start + line_height - 1;
		if (draw_end >= W_HEIGHT)
			draw_end = W_HEIGHT - 1;


		//TODO textures
		/*
		For each vertical stripe (line) you draw for a wall:
		Determine where on the texture’s X-axis the ray hit (texture coordinate).
		Scale the texture’s vertical pixels to the height of the wall slice on screen.
		Draw each pixel on that vertical line with the corresponding pixel from the texture.
		*/

		//assign wall texture
		t_texture *tex;

		tex = NULL;
		if (side == 0)//x grid line
		{
			if (raydir_x > 0) //WEST
				tex = &game->world->tex_WE;
			else //EAST
				tex = &game->world->tex_EA;
		}
		else
		{
			if (raydir_y > 0) //NORTH
				tex = &game->world->tex_NO;
			else //SOUTH
				tex = &game->world->tex_SO;
		}

		//wallhit location berechnen (img x achse um richtige vertikale linie ini texture auszuwählen)
		double	wall_x;
		int 	tex_x = 0; //x spalte in textur, dependig on width
		
		if (side == 0)
			wall_x = game->player->pos_y + wall_distance * raydir_y;
		else
			wall_x = game->player->pos_x + wall_distance * raydir_x;
		
		wall_x -= floor(wall_x); //only after 0. is needed
		
		tex_x = (int)(wall_x * tex->tex_width);
		if (side == 0 && raydir_x > 0)
			tex_x = tex->tex_width - tex_x - 1;
		if (side == 1 && raydir_y < 0)
			tex_x = tex->tex_width - tex_x - 1;


	//draw line
		//draw_wall_line(game, i, draw_start, draw_end, tex_x, tex); //i is vertical axis of image
		double step;
		int color_ceiling;
		int color_floor;
		int color_tex;
		double tex_pos;
		int tex_y;
		printf("starting drawing\n");

		if (tex_x < 0 || tex_x >= tex->tex_width) //debug
		{
			printf("Invalid tex_x: %d (tex_width: %d)\n", tex_x, tex->tex_width);
			tex_x = tex->tex_width / 2;  // or clamp it to something safe
		}


		color_ceiling = create_color(0, game->world->ceiling_r, game->world->ceiling_g, game->world->ceiling_b);
		color_floor = create_color(0, game->world->floor_r, game->world->floor_g, game->world->floor_b);

		step = (double)tex->tex_height / (double)line_height;
		printf("after step\n");

		// When wall line is taller than screen height
		double tex_offset = 0;
		if (line_height > W_HEIGHT)
		{
			// Calculate how much of the top of the texture to skip
			tex_offset = (line_height - W_HEIGHT) / 2.0 * step;
		}
		printf("after tex offset\n");
		
		// Starting texture coordinate
		tex_pos = tex_offset;
		
		// Now draw each screen pixel
		for (int y = 0; y < W_HEIGHT; y++)
		{
			if (y < draw_start)
			{
		
				my_mlx_pixel_put(game->image, y, i, color_ceiling);
			}
			else if (y >= draw_start && y <= draw_end)
			{
				tex_y = (int)tex_pos;
				if (tex_y < 0) tex_y = 0;
				if (tex_y >= tex->tex_height) tex_y = tex->tex_height - 1;
		
				color_tex = get_tex_color(tex_x, tex_y, tex);
				my_mlx_pixel_put(game->image, y, i, color_tex);
				tex_pos += step;
			}
			else
			{
				my_mlx_pixel_put(game->image, y, i, color_floor);
			}
		}		
		
		
		
		i++;
	}

}

int	game_loop(t_game *game)//TODO check if pos/dir changed, else no rendering/clearing
{
	if (*game->moved == true)
	{
		clear_image(game); //ok but super slow TODO

		raycast(game); //first frame
		//minimap (for understanding what is going on (movement)) (draw over everything else)
		minimap(game); //TODO dyn rezising of tiles
		mlx_put_image_to_window(game->mlx, game->window, game->image->img, 0, 0);
		//mlx_put_image_to_window(game->mlx, game->window, game->world->tex_NO.img, 0, 0);


		*game->moved = false;
	}
	return (0);
}


void	raycasting_main(t_game *game, bool *moved) //for now: lillis main
{
	//loop

		//0 init basics //TODO later after parsing
		init(game, moved);

	
	//1st img at startup:
	raycast(game); //first frame
	//minimap (for understanding what is going on (movement)) (draw over everything else)
	minimap(game); //TODO dyn rezising of tiles
	mlx_put_image_to_window(game->mlx, game->window, game->image->img, 0, 0);

	hooks(game); //TODO freeing 
	//add mlx loop hook ( -> raycast)
	
	mlx_loop_hook(game->mlx, game_loop, game);//keep re rendering

	
	//mlx_put_image_to_window(game->mlx, game->window, game->image->img, 0, 0);
	if (game->mlx)
		mlx_loop(game->mlx); //keeping window open
	
	
	//game_loop(game);



	
}
