/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:51:55 by lgottsch          #+#    #+#             */
/*   Updated: 2025/06/13 16:51:27 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*going thru map grid until wallhit
if		side = 0 : hit on x line
else hit on y line
*/
void	dda_loop(t_raycast *ray, t_game *game)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map_r[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

// distance to first coord grid is different, bc player somewehre in between
void	calc_dda_first_step(t_raycast *ray, t_game *game)
{
	if (ray->raydir.x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (game->player->pos_x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - game->player->pos_x)
			* ray->delta_dist_x;
	}
	if (ray->raydir.y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (game->player->pos_y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - game->player->pos_y)
			* ray->delta_dist_y;
	}
}

/* dda to get distance to wallhit
1e30 = huge num to avoid div/0
// printf("in map box x: %i y: %i\n", ray->map_x, ray->map_y);
*/
void	dda(t_raycast *ray, t_game *game)
{
	ray->map_x = (int)game->player->pos_x;
	ray->map_y = (int)game->player->pos_y;
	if (ray->raydir.x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = (double)fabs(1 / ray->raydir.x);
	if (ray->raydir.y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = (double)fabs(1 / ray->raydir.y);
	calc_dda_first_step(ray, game);
	dda_loop(ray, game);
}
