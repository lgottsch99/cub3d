/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:53:03 by lgottsch          #+#    #+#             */
/*   Updated: 2025/06/12 22:16:01 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* getting color value at pixel x,y in texture
calc pix address in mem
unsigned int bc color usually saved as 32 bit int
*/
int	get_tex_color(int x, int y, t_texture_r *tex)
{
	int		color;
	char	*pix;

	pix = tex->data_addr + (y * tex->size_line + x * (tex->bpp / 8));
	color = *(unsigned int *)pix;
	return (color);
}

/*
ray side == 0: x grid line
	raydir x > 0 ->west
	else east

ray side != 0 : y line
	raydir y > 0 -> North
	else: south
*/
void	assign_tex(t_raycast *ray, t_game *game)
{
	ray->tex = NULL;
	if (ray->side == 0)
	{
		if (ray->raydir.x > 0)
			ray->tex = &game->world->tex_we;
		else
			ray->tex = &game->world->tex_ea;
	}
	else
	{
		if (ray->raydir.y > 0)
			ray->tex = &game->world->tex_no;
		else
			ray->tex = &game->world->tex_so;
	}
}

//calc wallhit location 
//(tex img x axis to choose correct stripe from tex to draw)
void	calc_texture_hit(t_raycast *ray, t_game *game)
{
	ray->tex_x = 0;
	if (ray->side == 0)
		ray->wall_x = game->player->pos_y + ray->wall_distance * ray->raydir.y;
	else
		ray->wall_x = game->player->pos_x + ray->wall_distance * ray->raydir.x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * ray->tex->tex_width);
	if (ray->side == 0 && ray->raydir.x > 0)
		ray->tex_x = ray->tex->tex_width - ray->tex_x - 1;
	if (ray->side == 1 && ray->raydir.y < 0)
		ray->tex_x = ray->tex->tex_width - ray->tex_x - 1;
}
