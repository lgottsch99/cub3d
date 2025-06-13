/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:11:44 by lgottsch          #+#    #+#             */
/*   Updated: 2025/06/13 16:50:51 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Setting "camera" plane vectors to later also calc each ray
*/
void	set_plane(t_raycast *ray, t_game *game)
{
	ray->plane_len = tan((FOV * M_PI / 180.0) / 2.0);
	printf("plane len: %f\n", ray->plane_len);
	game->player->plane_x = (-1.0 * game->player->dir_y) * ray->plane_len;
	game->player->plane_y = game->player->dir_x * ray->plane_len;
	printf("plane vector x: %f y: %f\n", game->player->plane_x,
		game->player->plane_y);
}

/* calc each ray vector (each vertical i):
ray->len: represents horizontal position of the ray on the camera plane 
(rel to player dir)
then calcs the final vector of the ray that goes through i
*/
void	set_ray(t_raycast *ray, t_game *game, int i)
{
	ray->len = (2 * i) / (double)W_WIDTH - 1;
	ray->raydir.x = game->player->dir_x + game->player->plane_x * ray->len;
	ray->raydir.y = game->player->dir_y + game->player->plane_y * ray->len;
	// printf("direction of ray x: %f y: %f\n", ray->raydir.x, ray->raydir.y);
}

void	calc_wall_dist(t_raycast *ray, t_game *game)
{
	if (ray->side == 0)
		ray->wall_distance = (ray->map_x - game->player->pos_x
				+ (1 - ray->step_x) / 2) / ray->raydir.x;
	else
		ray->wall_distance = (ray->map_y - game->player->pos_y
				+ (1 - ray->step_y) / 2) / ray->raydir.y;
	// printf("WALL DIST: %f\n", ray->wall_distance);
}

//calc line hieght and highest and lowest pixel to draw in RENDERED IMG
void	calc_line_height(t_raycast *ray)
{
	ray->line_height = 0;
	ray->line_height = (int)(W_HEIGHT / ray->wall_distance);
	// printf("LINE HEIGHT: %f\n", ray->line_height);
	if (ray->line_height < 5)
		ray->line_height = 5;
	ray->draw_start = (W_HEIGHT - ray->line_height) / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->draw_start + ray->line_height - 1;
	if (ray->draw_end >= W_HEIGHT)
		ray->draw_end = W_HEIGHT - 1;
}
