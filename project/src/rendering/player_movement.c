/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:52:53 by lgottsch          #+#    #+#             */
/*   Updated: 2025/06/12 21:05:22 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

//change ->player->dir according to rotation matrix
int	change_orientation(int keycode, t_game *game)
{
	t_vector	new;
	t_vector	current;

	current.x = game->player->dir_x;
	current.y = game->player->dir_y;
	if (keycode == ARR_LEFT)
	{
		printf("LEFT pressed\n");
		new = v_rotate(360 - ROTATION_SPEED, current);
	}
	else if (keycode == ARR_RIGHT)
	{
		printf("RIGHT pressed\n");
		new = v_rotate(ROTATION_SPEED, current);
	}
	game->player->dir_x = new.x;
	game->player->dir_y = new.y;
	printf("new orientation x: %f\n", new.x);
	printf("new orientation y: %f\n", new.y);
	return (0);
}

void	check_and_update_move(t_game *game, t_vector *new)
{
	if (boundary_check(new, game) == 1)
	{
		printf("Not allowing out of bound moves\n");
		*game->moved = false;
		return ;
	}
	game->player->pos_x = new->x;
	game->player->pos_y = new->y;
}

void	move_w_s(int keycode, t_game *game)
{
	t_vector	new;
	t_vector	move;
	t_vector	normed;
	t_vector	current;

	current.x = game->player->pos_x;
	current.y = game->player->pos_y;
	normed = norm_vector(game->player->dir_x, game->player->dir_y);
	if (keycode == W_KEY)
	{
		printf("W pressed\n");
		move = v_change_len(MOVE_SPEED, normed.x, normed.y);
	}
	else
	{
		printf("S pressed\n");
		move = v_change_len((-1 * MOVE_SPEED), normed.x, normed.y);
	}
	new = v_add(current, move);
	check_and_update_move(game, &new);
	return ;
}

void	move_a_d(int keycode, t_game *game)
{
	t_vector	pos;
	t_vector	new;
	t_vector	move;
	t_vector	normed;
	t_vector	current;

	current.x = game->player->dir_x;
	current.y = game->player->dir_y;
	if (keycode == A_KEY)
	{
		printf("A pressed\n");
		new = v_rotate(270, current);
	}
	else
	{
		printf("D pressed\n");
		new = v_rotate(90, current);
	}
	normed = norm_vector(new.x, new.y);
	move = v_change_len(MOVE_SPEED, normed.x, normed.y);
	pos.x = game->player->pos_x;
	pos.y = game->player->pos_y;
	new = v_add(pos, move);
	check_and_update_move(game, &new);
	return ;
}
