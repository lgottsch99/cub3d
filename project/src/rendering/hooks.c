/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:20:44 by lgottsch          #+#    #+#             */
/*   Updated: 2025/05/17 15:11:06 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	quit_window(t_game *game)//TODO
{
	(void)game;
	ft_printf("x window\n");
	//free_everything TODO

	exit (0);
}

int	move(int keycode, t_game *game)//TODO validity check
{
	*game->moved = true;
	//moving needs to be along/according to direction vector TODO
	//each keypress = speed distance 

	if (keycode == ESC)
	{
		ft_printf("ESC pressed\n");
		//TODO free everything
		exit(0);
	}
	else if (keycode == W_KEY || keycode == S_KEY) //new
	{
		move_w_s(keycode, game);		
		return (0);
	}
	else if (keycode == A_KEY || keycode == D_KEY)
	{
		move_a_d(keycode, game);
		return (0);
	}
	else if (keycode == ARR_LEFT || keycode == ARR_RIGHT)
		change_orientation(keycode, game);
	else
		*game->moved = false;
	return (0);
}

void	hooks(t_game *game)
{
	//quitting window
	mlx_hook(game->window, ON_DESTROY, KeyPressMask, quit_window, game); //clicking x
	
	//movement
	mlx_hook(game->window, ON_KEYDOWN, KeyPressMask, move, game); //WASD, left right, esc
}