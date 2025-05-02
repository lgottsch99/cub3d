/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:17:07 by lgottsch          #+#    #+#             */
/*   Updated: 2025/05/02 14:10:48 by lgottsch         ###   ########.fr       */
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

//window 
#define W_HEIGHT 720 
#define W_WIDTH 1280

// STRUCTS ----------------------------------

typedef struct s_player
{
	//field of view
	//position
	int pos_x;
	int pos_y;
	
	//direction
	//...
} t_player;

//image mlx
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

//info about colors and textures
typedef struct s_world
{
	int floor_r; //floor color red (0-255)
	int floor_g; // green
	int floor_b; //blue
	int ceiling_r; //ceiling color red (0-255)
	int ceiling_g; 
	int ceiling_b;
	char *texture_NO; //path to texture
	char *texture_SO;
	char *texture_WE;
	char *texture_EA;
	
} t_world;

//big struct holding everything for easy handling + freeing
typedef struct s_game
{
	void	*mlx; //mlx pointer
	void	*window; //mlx window
	t_img	*image; //img to show on window
	char	**map;
	t_player *player; //ptr to player struct
	//...
	t_world	*world; //struct with parsed info 

} t_game;



// FUNCTIONS ----------------------------------

//raycasting.c
void	raycast(t_game *game);


#endif