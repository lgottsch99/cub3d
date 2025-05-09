/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Watanudon <Watanudon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:20:44 by lgottsch          #+#    #+#             */
/*   Updated: 2025/05/09 21:37:26 by Watanudon        ###   ########.fr       */
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
	(void)keycode;
	ft_printf("esc hook\n");
	if (keycode == 53) //XK_Escape) //esc = 53 on mac
	{
		//free_everything(big);
		exit(0);
	}
	else
		return 0;
	return (0);
}

/*
returns 0 if move valid, 1 if not
*/
int	boundary_check(t_vector *new, t_game *game)
{	
	// //math.h trunc() returns int part only, so 2.86757 -> 2

	//get int coord and check if either x +-1 = wall or y +- 1 = wall
	if (get_map_point(trunc(new->x), trunc(new->y), game) == 1)//
	{
		printf("move would be going inside wall. not allowing\n");
		return (1);
	}
	// else //needed?
	// {
	// 	//check if too close to wall
	// 		//calc dist to any grid border
	// 		//if dist < Wall buffer, check if next tile in that dir is a wall
		

	// }
	
	// check if new is too close to wall box
	


	return (0);	
}

int change_orientation(int keycode, t_game *game) //change ->player->dir according to rotation matrix
{
	(void)game;
	// double	speed;

	// speed = 0.2;
	if (keycode == ARR_LEFT)
	{
		printf("LEFT pressed\n");
		return (0);
	}
	else if (keycode == ARR_RIGHT)
	{
		printf("RIGHT pressed\n");
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

	speed = 0.2;
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
		printf("A pressed\n");
		//calc new position (+ Speed distance 90degrees to vector dir on left side)
		return (0);
	}
	else if (keycode == D_KEY) //move right
	{
		printf("D pressed\n");
		//calc new position (+ Speed distance 90degrees to vector dir on right side)
		return (0);
	}
	else
		return (0);

}


void	hooks(t_game *game) //all hooks together doesnt work
{
	//quitting window
	// mlx_hook(game->window, ON_KEYDOWN, KeyPressMask, destroy_esc, game); //pressing esc
	// mlx_hook(game->window, ON_DESTROY, KeyPressMask, quit_window, game); //clicking x
	
	// //movement

	// mlx_hook(game->window, ON_KEYDOWN, KeyPressMask, change_orientation, game); //left / right arrow
	mlx_hook(game->window, ON_KEYDOWN, KeyPressMask, move, game); //WASD
}