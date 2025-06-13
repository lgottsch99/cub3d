/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:52:01 by lgottsch          #+#    #+#             */
/*   Updated: 2025/06/13 13:49:07 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"




void	free_img(t_img_r *image)
{
	printf("in free img\n");
	if (image->img)
		free(image->img);
}

void	free_texture(t_texture_r *tex, t_game *game)
{
	if (tex->img)
	{
		printf("freeing texture img\n");
		mlx_destroy_image(game->mlx, tex->img);
		tex->img = NULL;
	}
	if (tex->relative_path)
	{
		printf("freeing texture rel path\n");
		tex->relative_path = NULL;
	}
	if (tex->data_addr)
	{
		printf("freeing texture data addr\n");
		tex->data_addr = NULL;
	}
	tex = NULL;
}

void	free_world(t_world *world, t_game *game)
{
	free_texture(&world->tex_no, game);
	free_texture(&world->tex_so, game);
	free_texture(&world->tex_we, game);
	free_texture(&world->tex_ea, game);
}

void	continue_free(t_game *game, int int_exit)
{
	if (game->player)
	{
		printf("freeing player\n");
		free(game->player);
		game->player = NULL;
	}
	if (game->world)
	{
		printf("freeing world\n");
		free_world(game->world, game);
		free(game->world);
		game->world = NULL;
	}
	if (game->mlx)
	{
		ft_printf("freeing mlx\n");
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (int_exit == 1)
		exit(0);
}

void	free_everything(t_game *game, int int_exit)
{	printf("IN FREE EVRYTINH\n");
	free_game(game);
	if (game->image && game->mlx && game->image->img)
	{
		printf("free image\n");
		mlx_destroy_image(game->mlx, game->image->img);
		game->image->img = NULL;
		free_img(game->image);
	}
	if (game->window && game->mlx)
	{
		ft_printf("freeing window\n");
		mlx_destroy_window(game->mlx, game->window);
		game->window = NULL;
	}
	if (game->image)
		free(game->image);
	if (game->map_r)
	{
		printf("freeing map\n");
		game->map_r = NULL;
	}
	continue_free(game, int_exit);
}
