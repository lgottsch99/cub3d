/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Watanudon <Watanudon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:20:44 by lgottsch          #+#    #+#             */
/*   Updated: 2025/05/13 11:30:34 by Watanudon        ###   ########.fr       */
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

	// //math.h trunc() returns int part only, so 2.86757 -> 2

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
	while (random_x <= new->x)
	{
		random_x += step;
		b = game->player->pos_y - m * game->player->pos_x;
		random_y = m * random_x + b;
		if (get_map_point(trunc(random_y), trunc(random_x), game) == 1)
		{
			printf("move would be going through wall. not allowing\n");
			return (1);
		}
	}
	//check if new point = wall

	return (0);	
}

int change_orientation(int keycode, t_game *game) //change ->player->dir according to rotation matrix
{
	(void)game;
	int	speed;

	t_vector	new; //new position/ orientation
	t_vector	current; //position or orientation

	speed = ROTATION_SPEED;
	if (keycode == ARR_LEFT)
	{
		printf("LEFT pressed\n");
		//get current orientation
		current.x = game->player->dir_x;
		current.y = game->player->dir_y;

		//rotate
		new = v_rotate(360 - speed, current);

		game->player->dir_x = new.x;
		game->player->dir_y = new.y;
		printf("new orientation x: %f\n", new.x);
		printf("new orientation y: %f\n", new.y);

		return (0);
	}
	else if (keycode == ARR_RIGHT)
	{
		printf("RIGHT pressed\n");

		current.x = game->player->dir_x;
		current.y = game->player->dir_y;

		//rotate
		new = v_rotate(speed, current);

		game->player->dir_x = new.x;
		game->player->dir_y = new.y;
		printf("new orientation x: %f\n", new.x);
		printf("new orientation y: %f\n", new.y);

		return (0);
	}
	else
		return (0);
}

int	move(int keycode, t_game *game)//TODO validity check
{
	*game->moved = true;
	//moving needs to be along/according to direction vector TODO
	//each keypress = speed distance 
	double		speed;
	t_vector	new; //new position/ orientation
	t_vector	move;//movement vector
	t_vector	normed;
	t_vector	current; //position or orientation

	speed = MOVE_SPEED;
	if (keycode == ESC)
	{
		ft_printf("ESC pressed\n");
		//TODO free everything
		exit(0);
	}
	if (keycode == W_KEY) //move forward
	{
		printf("W pressed\n");
		//take current position
		current.x = game->player->pos_x;
		current.y = game->player->pos_y;
	
		//get length of speed x dir (nur anteil um wie viel verscoben werden soll)
			//orientierung normieren 
			normed = norm_vector(game->player->dir_x, game->player->dir_y);
			//o auf länge = speed stutzen
			move = v_change_len(speed, normed.x, normed.y);
			
			//current pos + neue länge (vector addition)
			new = v_add(current, move);

			//check if new pos is out of bounds TODO
			//check if new pos is out of bounds TODO
			if (boundary_check(&new, game) == 1)
			{
				printf("Not allowing out of bound moves\n");
				*game->moved = false;
				return (0);
			}


			//set players new position //  IF OUT OF BOUNDS OK TODO
			game->player->pos_x = new.x;
			game->player->pos_y = new.y;
			printf("current x: %f\n", current.x);
			printf("current y: %f\n", current.y);
			printf("new x: %f\n", new.x);
			printf("new y: %f\n", new.y);

			return (0);
	}
	else if (keycode == S_KEY) //move back
	{
		printf("S pressed\n");
		//calc new position (+ Speed distance in opp direction of vector dir)
		//take current position
		current.x = game->player->pos_x;
		current.y = game->player->pos_y;

		//orientierung normieren 
		normed = norm_vector(game->player->dir_x, game->player->dir_y);
		//o auf länge = - 1 * speed stutzen! (-1 * speed for opposite direction)
		move = v_change_len((-1 * speed), normed.x, normed.y); 
		//current pos + neue länge (vector addition)
		new = v_add(current, move);

		//check if new pos is out of bounds TODO
		if (boundary_check(&new, game) == 1)
		{
			printf("Not allowing out of bound moves\n");
			*game->moved = false;
			return (0);
		}

		//set players new position IF OUT OF BOUNDS OK TODO
		game->player->pos_x = new.x;
		game->player->pos_y = new.y;
		printf("current x: %f\n", current.x);
		printf("current y: %f\n", current.y);
		printf("new x: %f\n", new.x);
		printf("new y: %f\n", new.y);
		
		return (0);
	}
 
	else if (keycode == A_KEY) //move left
	{
		t_vector	pos;
		printf("A pressed\n");
		//get orientation
		current.x = game->player->dir_x;
		current.y = game->player->dir_y;
		
		//rotate orientation 270 degrees against clock
		new = v_rotate(270, current);
		//norm
		normed = norm_vector(new.x, new.y);
		//länge stutzen
		move = v_change_len(speed, normed.x, normed.y);
		//current pos + neue länge (vector addition)
		pos.x = game->player->pos_x;
		pos.y = game->player->pos_y;
		new = v_add(pos, move);

		//boundary check
		//check if new pos is out of bounds TODO
		if (boundary_check(&new, game) == 1)
		{
			printf("Not allowing out of bound moves\n");
			*game->moved = false;
			return (0);
		}
		
		//assign new values
		game->player->pos_x = new.x;
		game->player->pos_y = new.y;
		printf("current x: %f\n", pos.x);
		printf("current y: %f\n", pos.y);
		printf("new x: %f\n", new.x);
		printf("new y: %f\n", new.y);

		
		return (0);
	}
	else if (keycode == D_KEY) //move right
	{
		printf("D pressed\n");
		//calc new position (+ Speed distance 90degrees to vector dir on right side)
		
		t_vector	pos;
		//get orientation
		current.x = game->player->dir_x;
		current.y = game->player->dir_y;
		
		//rotate orientation 90 degrees against clock
		new = v_rotate(90, current);
		//norm
		normed = norm_vector(new.x, new.y);
		//länge stutzen
		move = v_change_len(speed, normed.x, normed.y);
		//current pos + neue länge (vector addition)
		pos.x = game->player->pos_x;
		pos.y = game->player->pos_y;
		new = v_add(pos, move);

		//boundary check
		//check if new pos is out of bounds TODO
		if (boundary_check(&new, game) == 1)
		{
			printf("Not allowing out of bound moves\n");
			*game->moved = false;
			return (0);
		}
		
		//assign new values
		game->player->pos_x = new.x;
		game->player->pos_y = new.y;
		printf("current x: %f\n", pos.x);
		printf("current y: %f\n", pos.y);
		printf("new x: %f\n", new.x);
		printf("new y: %f\n", new.y);
		
		return (0);
	}
	if (keycode == ARR_LEFT || keycode == ARR_RIGHT)
	{
		change_orientation(keycode, game);
	}
	return (0);

}

void	hooks(t_game *game) //all hooks together doesnt work
{
	//quitting window
	mlx_hook(game->window, ON_DESTROY, KeyPressMask, quit_window, game); //clicking x
	
	// //movement

	// mlx_hook(game->window, ON_KEYDOWN, KeyPressMask, change_orientation, game); //left / right arrow
	mlx_hook(game->window, ON_KEYDOWN, KeyPressMask, move, game); //WASD
}