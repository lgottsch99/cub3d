/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:52:53 by lgottsch          #+#    #+#             */
/*   Updated: 2025/05/17 15:09:58 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cub3d.h"


int change_orientation(int keycode, t_game *game) //change ->player->dir according to rotation matrix
{
	t_vector	new; //new position/ orientation
	t_vector	current; //position or orientation

	current.x = game->player->dir_x;
	current.y = game->player->dir_y;
	if (keycode == ARR_LEFT)
	{
		printf("LEFT pressed\n");
		//rotate
		new = v_rotate(360 - ROTATION_SPEED, current);
	}
	else if (keycode == ARR_RIGHT)
	{
		printf("RIGHT pressed\n");
		//rotate
		new = v_rotate(ROTATION_SPEED, current);
	}
	game->player->dir_x = new.x;
	game->player->dir_y = new.y;
	printf("new orientation x: %f\n", new.x);
	printf("new orientation y: %f\n", new.y);
	return (0);
}

void	move_w_s(int keycode, t_game *game)
{
	t_vector	new; //new position/ orientation
	t_vector	move;//movement vector
	t_vector	normed;
	t_vector	current; //position or orientation

	current.x = game->player->pos_x;
	current.y = game->player->pos_y;
	//orientation norming to length 1
	normed = norm_vector(game->player->dir_x, game->player->dir_y);
	//change length to step distance
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
	//calc new position after movement
	new = v_add(current, move);
	//check if new pos is out of bounds TODO
	if (boundary_check(&new, game) == 1)
	{
		printf("Not allowing out of bound moves\n");
		*game->moved = false;
		return;
	}
	//set players new position //  IF OUT OF BOUNDS OK TODO
	game->player->pos_x = new.x;
	game->player->pos_y = new.y;
	printf("current x: %f\n", current.x);
	printf("current y: %f\n", current.y);
	printf("new x: %f\n", new.x);
	printf("new y: %f\n", new.y);
	return;
}

void	move_a_d(int keycode, t_game *game)
{
	t_vector	pos;
	t_vector	new; //new position/ orientation
	t_vector	move;//movement vector
	t_vector	normed;
	t_vector	current; //position or orientation
		
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
	//norm
	normed = norm_vector(new.x, new.y);
	//länge stutzen
	move = v_change_len(MOVE_SPEED, normed.x, normed.y);
	//current pos + neue länge (vector addition)
	pos.x = game->player->pos_x;
	pos.y = game->player->pos_y;
	new = v_add(pos, move);
	//boundary check//check if new pos is out of bounds TODO
	if (boundary_check(&new, game) == 1)
	{
		printf("Not allowing out of bound moves\n");
		*game->moved = false;
		return;
	}
	//assign new values
	game->player->pos_x = new.x;
	game->player->pos_y = new.y;
	printf("current x: %f\n", pos.x);
	printf("current y: %f\n", pos.y);
	printf("new x: %f\n", new.x);
	printf("new y: %f\n", new.y);
	return;
}
