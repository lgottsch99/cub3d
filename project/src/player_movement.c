/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:52:53 by lgottsch          #+#    #+#             */
/*   Updated: 2025/05/16 19:20:16 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cub3d.h"

/*
returns 0 if move valid, 1 if not
*/
int	boundary_check(t_vector *new, t_game *game) //TODO: check if any point on line next step = wall hit, not only end point (=going thru walls rn)
{	
	double	m;//steigung
	double	b; //y achsenabschnitt
	double	random_x;
	double	random_y;
	double step;

	//get int coord and check if either x +-1 = wall or y +- 1 = wall
	if (get_map_point(trunc(new->y), trunc(new->x), game) == 1)//
	{
		printf("move would be going inside wall. not allowing\n");
		return (1);
	}
	// check each box the distance from player to end position passes, if any is 1 dont move
		//get steigung der geraden (neuer punktk = y = mx + b)
	//traverse in 0.1? abständen or even smaller

	step = 0.0000001;

	random_x = game->player->pos_x; //x point to traverse
	m = (new->y - game->player->pos_y) / (new->x - game->player->pos_x);
	while (random_x <= new->x) //do same for y
	{
		random_x += step;
		b = game->player->pos_y - m * game->player->pos_x;
		random_y = m * random_x + b;
		//check if new point = wall
		if (get_map_point(trunc(random_y), trunc(random_x), game) == 1)
		{
			printf("move would be going through wall. not allowing\n");
			return (1);
		}
	}
	//maybe even add logic that if both +1 coords = wall dont allow in certain dir?
	random_y = game->player->pos_y; //x point to traverse
	m = (new->x - game->player->pos_x) / (new->y - game->player->pos_y);
	while (random_x <= new->x) //do same for y
	{
		random_y += step;
		b = game->player->pos_x - m * game->player->pos_y;
		random_x = m * random_y + b;
		//check if new point = wall
		if (get_map_point(trunc(random_y), trunc(random_x), game) == 1)
		{
			printf("move would be going through wall. not allowing\n");
			return (1);
		}
	}


	//TODO change logic to check if gerade to go -> crossing grid lines that are walls
	return (0);	
}


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
