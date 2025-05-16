#include "../includes/cub3d.h"


void	free_img(t_img	*image)
{
	if (image->img)
		free(image->img);
	if (image->addr)
		free(image->addr);

}

void	free_texture(t_texture *tex, t_game *game)
{
	if (tex->relative_path)
		free(tex->relative_path);
	if (tex->img) //?? 
	{
		ft_printf("freeing tex image\n");
		mlx_destroy_image(game->mlx, tex->img);
		free(tex->img);
	}
	if (tex->data_addr)
		free(tex->data_addr);
	
}

void	free_world(t_world *world, t_game *game)
{
	if (world.tex_NO)
		free_texture(&world.tex_NO, game);
	if (world.tex_SO)
		free_texture(&world.tex_SO, game);
	if (world.tex_WE)
		free_texture(&world.tex_WE, game);
	if (world.tex_EA)
		free_texture(&world.tex_EA, game);
}

void	free_everything(t_game *game)
{
	if (game->image && game->mlx && game->image->img)
	{
		ft_printf("freeing image\n");
		mlx_destroy_image(game->mlx, game->image->img);
		free(game->image);
	}
	if (game->window && game->mlx)
	{
		ft_printf("freeing window\n");
		mlx_destroy_window(game->mlx, game->window);
	}


	// if (game->image) //needed after top part?
	// 	free_img(game->image);

	if (game->map)

	if (game->player) //set to null only 
		game->player = NULL;

	if (game->world) //free textures
		free_world(game->world, game);
	if (game->mlx)
	{
		ft_printf("freeing mlx\n");
		//mlx_destroy_display(game->mlx);
		free(game->mlx);
	}

}