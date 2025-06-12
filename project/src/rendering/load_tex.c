/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:04:14 by lgottsch          #+#    #+#             */
/*   Updated: 2025/06/12 20:21:43 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void load_NO(t_game *game)
{
	game->world->tex_NO.relative_path = game->No_texture.path;
	game->world->tex_NO.img = mlx_xpm_file_to_image(game->mlx, game->world->tex_NO.relative_path, &game->world->tex_NO.tex_width, &game->world->tex_NO.tex_height);
	if (game->world->tex_NO.img == NULL)
	{
		printf("LOADING NO TEXTURE FAILED\n");
		free_everything(game, 1);
	}
	game->world->tex_NO.data_addr = mlx_get_data_addr(game->world->tex_NO.img, &game->world->tex_NO.bpp, &game->world->tex_NO.size_line, &game->world->tex_NO.endian);
	if (game->world->tex_NO.data_addr == NULL)
	{
		printf("getting NO TEXTURE addr FAILED\n");
		free_everything(game, 1);
	}
}

void load_SO(t_game *game)
{
	game->world->tex_SO.relative_path = game->So_texture.path; // "../Textures_xpm/Planet2.xpm";
	game->world->tex_SO.img = mlx_xpm_file_to_image(game->mlx, game->world->tex_SO.relative_path, &game->world->tex_SO.tex_width, &game->world->tex_SO.tex_height);
	if (game->world->tex_SO.img == NULL)
	{
		printf("LOADING SO TEXTURE FAILED\n");
		free_everything(game, 1);
	}
	game->world->tex_SO.data_addr = mlx_get_data_addr(game->world->tex_SO.img, &game->world->tex_SO.bpp, &game->world->tex_SO.size_line, &game->world->tex_SO.endian);
	if (game->world->tex_SO.data_addr == NULL)
	{
		printf("getting SO TEXTURE addr FAILED\n");
		free_everything(game, 1);
	}
}

void load_WE(t_game *game)
{
	game->world->tex_WE.relative_path = game->We_texture.path;
	game->world->tex_WE.img = mlx_xpm_file_to_image(game->mlx, game->world->tex_WE.relative_path, &game->world->tex_WE.tex_width, &game->world->tex_WE.tex_height);
	if (game->world->tex_WE.img == NULL)
	{
		printf("LOADING WE TEXTURE FAILED\n");
		free_everything(game, 1);
	}
	game->world->tex_WE.data_addr = mlx_get_data_addr(game->world->tex_WE.img, &game->world->tex_WE.bpp, &game->world->tex_WE.size_line, &game->world->tex_WE.endian);
	if (game->world->tex_WE.data_addr == NULL)
	{
		printf("getting WE TEXTURE addr FAILED\n");
		free_everything(game, 1);
	}
}

void load_EA(t_game *game)
{
	game->world->tex_EA.relative_path = game->Ea_texture.path;
	game->world->tex_EA.img = mlx_xpm_file_to_image(game->mlx, game->world->tex_EA.relative_path, &game->world->tex_EA.tex_width, &game->world->tex_EA.tex_height);
	if (game->world->tex_EA.img == NULL)
	{
		printf("LOADING EA TEXTURE FAILED\n");
		free_everything(game, 1);
	}
	game->world->tex_EA.data_addr = mlx_get_data_addr(game->world->tex_EA.img, &game->world->tex_EA.bpp, &game->world->tex_EA.size_line, &game->world->tex_EA.endian);
	if (game->world->tex_EA.data_addr == NULL)
	{
		printf("getting EA TEXTURE addr FAILED\n");
		free_everything(game, 1);
	}
}


