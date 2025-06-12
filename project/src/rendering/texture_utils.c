/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:53:03 by lgottsch          #+#    #+#             */
/*   Updated: 2025/05/29 14:32:40 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


/* getting color value at pixel x,y in texture
*/
int	get_tex_color(int x, int y, t_texture_r *tex)
{
	int		color;
	char	*pix; //pointer to pix

	//calc pix address in mem
	pix = tex->data_addr + (y * tex->size_line + x * (tex->bpp / 8));

	//unsigned int bc color usually saved as 32 bit int
	color = *(unsigned int *)pix;
	return (color);
}

void	assign_tex(t_raycast *ray, t_game *game)
{
	ray->tex = NULL;
	if (ray->side == 0)//x grid line
	{
		if (ray->raydir.x > 0) //WEST
			ray->tex = &game->world->tex_WE;
		else //EAST
			ray->tex = &game->world->tex_EA;
	}
	else
	{
		if (ray->raydir.y > 0) //NORTH
			ray->tex = &game->world->tex_NO;
		else //SOUTH
			ray->tex = &game->world->tex_SO;
	}
}

void	calc_texture_hit(t_raycast *ray, t_game *game)
{
	ray->tex_x = 0;
	if (ray->side == 0)
		ray->wall_x = game->player->pos_y + ray->wall_distance * ray->raydir.y;
	else
		ray->wall_x = game->player->pos_x + ray->wall_distance * ray->raydir.x;
	
	ray->wall_x -= floor(ray->wall_x); //only after 0. is needed
	
	ray->tex_x = (int)(ray->wall_x * ray->tex->tex_width);
	if (ray->side == 0 && ray->raydir.x > 0)
		ray->tex_x = ray->tex->tex_width - ray->tex_x - 1;
	if (ray->side == 1 && ray->raydir.y < 0)
		ray->tex_x = ray->tex->tex_width - ray->tex_x - 1;

}
