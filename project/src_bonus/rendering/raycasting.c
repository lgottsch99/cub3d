/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:10:57 by lgottsch          #+#    #+#             */
/*   Updated: 2025/06/12 21:55:57 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_loop(t_raycast *ray, t_game *game, double tex_pos, int i)
{
	int	color_tex;
	int	tex_y;
	int	y;

	y = 0;
	while (y < W_HEIGHT)
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
	double	tex_pos;
	double	tex_offset;

	ray->skip = (double)ray->tex->tex_height / (double)ray->line_height;
	tex_offset = 0;
	if (ray->line_height > W_HEIGHT)
		tex_offset = (ray->line_height - W_HEIGHT) / 2.0 * ray->skip;
	tex_pos = tex_offset;
	draw_loop(ray, game, tex_pos, i);
}

//loop to render single scene, each i is vertical pixel line
void	raycast(t_game *game)
{
	t_raycast	ray;
	int			i;

	set_plane(&ray, game);
	i = 0;
	while (i < W_WIDTH)
	{
		set_ray(&ray, game, i);
		dda(&ray, game);
		calc_wall_dist(&ray, game);
		calc_line_height(&ray);
		assign_tex(&ray, game);
		calc_texture_hit(&ray, game);
		draw_wall_line(&ray, game, i);
		i++;
	}
}

int	game_loop(t_game *game)
{
	if (*game->moved == true)
	{
		clear_image(game);
		raycast(game);
		minimap(game); //
		mlx_put_image_to_window(game->mlx, game->window,
			game->image->img, 0, 0);
		*game->moved = false;
	}
	return (0);
}

void	raycasting_main(t_game *game, bool *moved)
{
	init(game, moved);
	raycast(game);
	minimap(game); //
	mlx_put_image_to_window(game->mlx, game->window, game->image->img, 0, 0);
	hooks(game);
	mlx_loop_hook(game->mlx, game_loop, game);
	if (game->mlx)
		mlx_loop(game->mlx);
}
