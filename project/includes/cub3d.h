/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Watanudon <Watanudon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:17:07 by lgottsch          #+#    #+#             */
/*   Updated: 2025/05/11 13:15:15 by Watanudon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// LIBRARIES ----------------------------------

//# include "../lib/mlx_linux/mlx.h" //minilibx for graphics rendering LINUX
# include "../lib/mlx_mac/mlx.h" //minilibx for graphics rendering MAC

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
#include <stdbool.h>

#include "keycodes_mac.h" // only on mac
//#include "keycodes_linux.h" // only on linux


// MACROS ----------------------------------

//window 
#define W_HEIGHT 720 
#define W_WIDTH 1280

//player spawning orientation of FOV //TODO check if ok
# define N_X 0
# define N_Y -1

# define S_X 0
# define S_Y +1

# define E_X +1
# define E_Y 0

# define W_X -1
# define W_Y 0

//Field of view in degrees (range up to 180)
# define FOV 66

//buffer around walls
//# define WALL_BUFFER 0.1

//
# define ROTATION_SPEED 5

//Events
//event codes
enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

//event masks
# define KeyPressMask		(1L<<0)
# define KeyReleaseMask		(1L<<1)


// STRUCTS ----------------------------------

typedef struct s_vector
{
	double x;
	double y;
} t_vector;

typedef struct s_player //TODO change to vector structs
{
	//field of view
	//position
	//t_vector	pos;
	double pos_x;
	double pos_y;
	
	//direction (= vector (or camera): x and y coordinate)
	//t_vector	dir;
	double dir_x;
	double dir_y;

	//plane vector (=camera, based on FOV)
	//t_vector	plane;
	double plane_x;
	double plane_y;

	
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

typedef struct s_texture
{
	void	*img;
	char	*relative_path;
	int		tex_width;
	int		tex_height;
	
	char	*data_addr;
	int		bpp;
	int		size_line;
	int		endian;
} t_texture;

//info about colors and textures
typedef struct s_world
{
	int floor_r; //floor color red (0-255)
	int floor_g; // green
	int floor_b; //blue
	int ceiling_r; //ceiling color red (0-255)
	int ceiling_g; 
	int ceiling_b;
	t_texture tex_NO; //path to texture
	t_texture tex_SO;
	t_texture tex_WE;
	t_texture tex_EA;
	// char *texture_SO;
	// char *texture_WE;
	// char *texture_EA;
	int map_width; //needed for minimap
	int map_height;
	//char **world;
	
} t_world;

//big struct holding everything for easy handling + freeing
typedef struct s_game
{
	void	*mlx; //mlx pointer
	void	*window; //mlx window
	t_img	*image; //img to show on window
	char	**map; //INT would be better?
	//int **map;
	t_player *player; //ptr to player struct
	//...
	t_world	*world; //struct with parsed info 
	bool	*moved;

} t_game;

typedef struct s_line
{
	int x;
	int y;
	int draw_start; //index on img y axis
	int draw_end;
	int tex_x; //x coordinate of texture to draw
	int tex_y; //y coordinate of texture to draw
} t_line;




// FUNCTIONS ----------------------------------

//raycasting.c
void	raycasting_main(t_game *game, bool *moved); //for now: lillis main

//raycast_utils
void	draw_wall_line(t_game *game, int x, int draw_start, int draw_end, int color, int tex_x, t_texture *tex);

//vector math
t_vector	norm_vector(double x, double y);
t_vector	v_change_len(double k, double x, double y);
t_vector	v_add(t_vector a, t_vector b);
double		vector_len(double x, double y);
t_vector	v_rotate(int degrees, t_vector a);


//minimap
void	minimap(t_game *game);

//utils
int		create_color(int t, int r, int g, int b);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
int		get_map_point(int x,int y, t_game *game);

//hooks
void	hooks(t_game *game);
int		destroy_esc(int keycode, t_game *game);
int		quit_window(t_game *game);


#endif