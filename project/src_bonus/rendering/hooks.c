/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:20:44 by lgottsch          #+#    #+#             */
/*   Updated: 2025/06/12 22:18:57 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	quit_window(t_game *game)
{
	ft_printf("x window\n");
	free_everything(game, 1);
	return (0);
}

int	move(int keycode, t_game *game)
{
	*game->moved = true;
	if (keycode == ESC)
	{
		ft_printf("ESC pressed\n");
		free_everything(game, 1);
	}
	else if (keycode == W_KEY || keycode == S_KEY)
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
	mlx_hook(game->window, ON_DESTROY, (1L << 0), quit_window, game);
	mlx_hook(game->window, ON_KEYDOWN, (1L << 0), move, game);
}
