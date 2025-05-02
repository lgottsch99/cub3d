/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:17:07 by lgottsch          #+#    #+#             */
/*   Updated: 2025/05/02 11:50:20 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// LIBRARIES ----------------------------------

# include "../lib/mlx_linux/mlx.h" //minilibx for graphics rendering
# include "../lib/full_libft/full_libft.h"
# include <math.h>
//# include <X11/keysym.h> //defines some keycodes for hooks, only needed on linux?

//for event macros like KeyPress 
//https://codebrowser.dev/kde/include/X11/X.h.html
//#include <X.h> //needed on mac?

#include <stdio.h> //printf, perror
#include <stdlib.h> //malloc, free
#include <sys/types.h> //open
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> //read, write, exit
#include <string.h> //strerror
#include <sys/time.h> //gettimeofday


// MACROS ----------------------------------

// STRUCTS ----------------------------------

typedef struct s_player
{
	//field of view
	//position
	//direction
	//...
} t_player;


typedef struct s_game
{
	//mlx pointer
	//mlx window
	char **map;
	t_player *player; //ptr to player struct
	//...

} t_game;



// FUNCTIONS ----------------------------------



#endif