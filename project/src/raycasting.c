/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Watanudon <Watanudon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:10:57 by lgottsch          #+#    #+#             */
/*   Updated: 2025/05/16 10:09:02 by Watanudon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
approach:
	add textures
		load textures:
		at init store textures in some buffer, The buffer will be an array of integers, where each integer represents the colour of a pixel
	for each ray: 
		calc x coord of WHERE it hits the wall in coord grid -> same x coord 


		Textures:
		For each vertical stripe (line) you draw for a wall:
		Determine where on the texture’s X-axis the ray hit (texture coordinate).
		Scale the texture’s vertical pixels to the height of the wall slice on screen.
		Draw each pixel on that vertical line with the corresponding pixel from the texture.
		

TODO LILLI
	boundary check more complete KINDA OK
	movement smoother?
	framerate + speed dynamic? like always 10 steps / sec?

	freeing 

	bonus compilation


???:
	
*/

// actual raycasting
// 	get player pos and dir vector -> camera plane vector
// 	calc camera plane end points ->player pos to endpoints = outer most edges of fov/img
// 	divide distance into W_Width, for each pixel:
// 		calc vector from player to next wall hit
// 		calc vector distance , get height (and direction etc) of wall line to draw

#include "../includes/cub3d.h"

void	draw_loop(t_raycast *ray, t_game *game, double tex_pos, int i)
{
	int color_tex;
	int tex_y;
	int y;
	
	y = 0;
	while(y < W_HEIGHT)
	{
		if (y < ray->draw_start)
			my_mlx_pixel_put(game->image, y, i, game->world->color_ceiling);
		else if (y >= ray->draw_start && y <= ray->draw_end)
		{
			tex_y = (int)tex_pos;
			if (tex_y < 0)
				tex_y = 0;
			if (tex_y >= ray->tex->tex_height)
				tex_y = ray->tex->tex_height - 1;
	
			color_tex = get_tex_color(ray->tex_x, tex_y, ray->tex);
			my_mlx_pixel_put(game->image, y, i, color_tex);
			tex_pos += ray->skip;
		}
		else
			my_mlx_pixel_put(game->image, y, i, game->world->color_floor);
		y++;
	}
}


void	draw_wall_line(t_raycast *ray, t_game *game, int i)
{
	double tex_pos;

	ray->skip = (double)ray->tex->tex_height / (double)ray->line_height;

	// If wall line bigger than screen height
	double tex_offset = 0;
	if (ray->line_height > W_HEIGHT)
	{
		// Calculate how much of the top of the texture to skip
		tex_offset = (ray->line_height - W_HEIGHT) / 2.0 * ray->skip;
	}	
	// Starting texture coordinate
	tex_pos = tex_offset;

	draw_loop(ray, game, tex_pos, i);
}

void	raycast(t_game *game)
{
	t_raycast	ray;
	int			i;

	set_plane(&ray, game);

//raycasting loop () to render single scene
	i = 0;
	while (i < W_WIDTH) //for each vertical line (= each i in width of window)
	{
		//each ray is sum of player pos + dir =/- part of plane (camera x?multiplier of plane len)
		//double len; //multiplier for current i location in window -> length of plane vector
		set_ray(&ray, game, i);

	//--- dda -----------
		dda(&ray, game);

	//calc distance of ray to wall
		calc_wall_dist(&ray, game);
		
	//calc height of line to draw
		calc_line_height(&ray);

	//assign wall texture
		assign_tex(&ray, game);

	//wallhit location berechnen (img x achse um richtige vertikale linie ini texture auszuwählen)
		calc_texture_hit(&ray, game);
		
	//draw line
		draw_wall_line(&ray, game, i);

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

}
