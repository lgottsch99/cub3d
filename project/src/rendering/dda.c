/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:51:55 by lgottsch          #+#    #+#             */
/*   Updated: 2025/06/12 16:31:19 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	dda_loop(t_raycast *ray, t_game *game)
{
	printf("going into dda loop\n");
	int hit = 0; //stop once wallhit

	while (hit == 0)
	{
		printf("in dda loop\n");
		//jump to next map square-> either in x or y direction
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0; //side on x line
		}
		else
		{
			ray->sidedist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1; //side on y line
		}
		//check if wallhit
		if (game->map_r[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}

}

void	calc_dda_first_step(t_raycast *ray, t_game *game)
{
	if (ray->raydir.x < 0)
	{
		ray->step_x = -1;
		//distance from the ray starting position to the first side to the left
		ray->sidedist_x = (game->player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		//the first side to the right is used instead
		ray->sidedist_x = (ray->map_x + 1.0 - game->player->pos_x) * ray->delta_dist_x;
	}

	if (ray->raydir.y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (game->player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - game->player->pos_y) * ray->delta_dist_y;
	}

}

void	dda(t_raycast *ray, t_game *game)
{
	printf("setting up dda vars\n");
	//which box of map are we in
	ray->map_x = (int) game->player->pos_x; 
	ray->map_y = (int) game->player->pos_y;
	printf("in box x: %i y: %i\n", ray->map_x, ray->map_y);

	//length the ray must travel to move from one x-side (vertical line) to the next, or one y-side (horizontal line) to the next
	if (ray->raydir.x == 0)
		ray->delta_dist_x = 1e30; //huge num to avoid div/0
	else
		ray->delta_dist_x = (double) fabs(1 / ray->raydir.x);

	if (ray->raydir.y == 0)
		ray->delta_dist_y = 1e30; //huge num to avoid div/0 9so big that line will never cross that axis)
	else
		ray->delta_dist_y = (double) fabs(1 / ray->raydir.y);


//calc first stepX, stepY, and the initial sideDistX and sideDistY before dda can start
	calc_dda_first_step(ray, game);

//dda loop calc ----------------
	dda_loop(ray, game);
}

