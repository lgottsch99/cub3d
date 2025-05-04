/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:20:44 by lgottsch          #+#    #+#             */
/*   Updated: 2025/05/04 18:27:32 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


int	quit_window(t_game *game)//TODO
{
	(void)game;
	ft_printf("x window\n");
	//free_everything(big);
	exit (0);
}

//int is passed by internal event handler
int	destroy_esc(int keycode, t_game *game) //TODO
{
	(void)game;
	ft_printf("esc hook\n");
	if (keycode == XK_Escape)
	{
		//free_everything(big);
		exit(0);
	}
	else
		return 0;
}

void	hooks(t_game *game)
{
	mlx_hook(game->window, 2, 1L << 0, destroy_esc, game); //pressing esc
	mlx_hook(game->window, 17, 1L << 0, quit_window, game); //clicking x
}