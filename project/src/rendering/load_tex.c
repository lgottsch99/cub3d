/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:04:14 by lgottsch          #+#    #+#             */
/*   Updated: 2025/06/12 22:06:56 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	load_no(t_game *game)
{
	game->world->tex_no.relative_path = game->no_texture.path;
	game->world->tex_no.img = mlx_xpm_file_to_image(game->mlx,
			game->world->tex_no.relative_path, &game->world->tex_no.tex_width,
			&game->world->tex_no.tex_height);
	if (game->world->tex_no.img == NULL)
	{
		printf("LOADING NO TEXTURE FAILED\n");
		free_everything(game, 1);
	}
	game->world->tex_no.data_addr = mlx_get_data_addr(game->world->tex_no.img,
			&game->world->tex_no.bpp, &game->world->tex_no.size_line,
			&game->world->tex_no.endian);
	if (game->world->tex_no.data_addr == NULL)
	{
		printf("getting NO TEXTURE addr FAILED\n");
		free_everything(game, 1);
	}
}

void	load_so(t_game *game)
{
	game->world->tex_so.relative_path = game->so_texture.path;
	game->world->tex_so.img = mlx_xpm_file_to_image(game->mlx,
			game->world->tex_so.relative_path, &game->world->tex_so.tex_width,
			&game->world->tex_so.tex_height);
	if (game->world->tex_so.img == NULL)
	{
		printf("LOADING so TEXTURE FAILED\n");
		free_everything(game, 1);
	}
	game->world->tex_so.data_addr = mlx_get_data_addr(game->world->tex_so.img,
			&game->world->tex_so.bpp, &game->world->tex_so.size_line,
			&game->world->tex_so.endian);
	if (game->world->tex_so.data_addr == NULL)
	{
		printf("getting SO TEXTURE addr FAILED\n");
		free_everything(game, 1);
	}
}

void	load_we(t_game *game)
{
	game->world->tex_we.relative_path = game->we_texture.path;
	game->world->tex_we.img = mlx_xpm_file_to_image(game->mlx,
			game->world->tex_we.relative_path, &game->world->tex_we.tex_width,
			&game->world->tex_we.tex_height);
	if (game->world->tex_we.img == NULL)
	{
		printf("LOADING we TEXTURE FAILED\n");
		free_everything(game, 1);
	}
	game->world->tex_we.data_addr = mlx_get_data_addr(game->world->tex_we.img,
			&game->world->tex_we.bpp, &game->world->tex_we.size_line,
			&game->world->tex_we.endian);
	if (game->world->tex_we.data_addr == NULL)
	{
		printf("getting WE TEXTURE addr FAILED\n");
		free_everything(game, 1);
	}
}

void	load_ea(t_game *game)
{
	game->world->tex_ea.relative_path = game->ea_texture.path;
	game->world->tex_ea.img = mlx_xpm_file_to_image(game->mlx,
			game->world->tex_ea.relative_path, &game->world->tex_ea.tex_width,
			&game->world->tex_ea.tex_height);
	if (game->world->tex_ea.img == NULL)
	{
		printf("LOADING ea TEXTURE FAILED\n");
		free_everything(game, 1);
	}
	game->world->tex_ea.data_addr = mlx_get_data_addr(game->world->tex_ea.img,
			&game->world->tex_ea.bpp, &game->world->tex_ea.size_line,
			&game->world->tex_ea.endian);
	if (game->world->tex_ea.data_addr == NULL)
	{
		printf("getting EA TEXTURE addr FAILED\n");
		free_everything(game, 1);
	}
}
