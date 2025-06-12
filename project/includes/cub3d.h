/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:17:07 by lgottsch          #+#    #+#             */
/*   Updated: 2025/06/12 16:28:43 by lgottsch         ###   ########.fr       */
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

//#include "keycodes_mac.h" // only on mac
#include "keycodes_linux.h" // only on linux

#include "./maps.h"
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

# define ROTATION_SPEED 4
# define MOVE_SPEED 0.3

//Player 'Body'
# define PLAYER_RADIUS 0.1

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

/* Connection btw parsing + rendering
INFO NEEDED FOR RENDERING:

	player start pos x
	player start pos y

	player direction: N S E or W 

	floor color (r g b or final value)
	ceiling color (r g b or final value)

	Texture paths
		NO
		SO
		EA
		WE
	
	char **map
	map height
	map width

*/




typedef struct s_vector
{
	double x;
	double y;
} t_vector;

typedef struct s_player //TODO change to vector structs
{
	//position
	double pos_x;
	double pos_y;
	
	//direction (= vector (or camera): x and y coordinate)
	double dir_x;
	double dir_y;

	//plane vector (=camera, based on FOV)
	double plane_x;
	double plane_y;

} t_player;

//image mlx
typedef struct s_img_r
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img_r;

typedef struct s_texture_r //r for rendering
{
	void	*img; //image pointer to loaded texture
	char	*relative_path; //path to texture file
	int		tex_width; 
	int		tex_height; 

	//TEX IMG INFO
	char	*data_addr; 
	int		bpp;
	int		size_line;
	int		endian;
} t_texture_r;

//info about colors and textures
typedef struct s_world
{
	int floor_r; //floor color red (0-255)
	int floor_g; // green
	int floor_b; //blue
	int	color_floor;

	int ceiling_r; //ceiling color red (0-255)
	int ceiling_g; 
	int ceiling_b;
	int	color_ceiling;

	t_texture_r tex_NO; //path to texture
	t_texture_r tex_SO;
	t_texture_r tex_WE;
	t_texture_r tex_EA;
	
} t_world;


typedef struct s_game //parsing version
{///parsing
	void			*mlx;
	void			*window;
	t_img			*image_p;
	t_map			map;
	t_texture		No_texture;
	t_texture		So_texture;
	t_texture		We_texture;
	t_texture		Ea_texture;
	t_color			ceiling;
	t_color			floor;

	///rendering
	// void	*mlx; //mlx pointer
	// void	*window; //mlx window
	t_img_r	*image; //ptr to final img struct to show on window

	char	**map_r; //change to t_map

	t_player *player; //ptr to player struct

	t_world	*world; //maybe not needed, change
	
	bool	*moved; //ptr to movement indicator bool in main

}					t_game;


typedef struct s_line
{
	int x;
	int y;
	int draw_start; //index on img y axis
	int draw_end;
	int tex_x; //x coordinate of texture to draw
	int tex_y; //y coordinate of texture to draw
} t_line;

typedef struct s_raycast
{
	double		plane_len;
	t_vector	raydir;
	double		len; //multiplier for current i location in window -> length of plane vector
	double		wall_distance;
	double		line_height;
	int			draw_start;
	int			draw_end;
	int			side;
	double		skip;
	
	//dda parts
	int			map_x; //which box of map are we in
	int			map_y;
	double		sidedist_x; //len of ray from current pos to next x or y side
	double		sidedist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x; //=1 or -1 depending on direction of ray thru grid
	int			step_y;

	//texture calculation
	t_texture_r	*tex; //pointer to texture to draw
	double		wall_x; //point ray hits texture vertically on map
	int			tex_x; //corresponding x pix row in tex img
	
} t_raycast;

typedef struct s_boundary
{
	double player_radius;
	
	double	step;
	int		amount_steps;
	double	x_step;
	double	y_step;

	int		max_x;
	int		min_x;
	int 	max_y;
	int		min_y;

	double	x;
	double	y;

} t_boundary;


// FUNCTIONS ----------------------------------


//init
void	init(t_game *game, bool *moved);

//raycasting.c
void	raycasting_main(t_game *game, bool *moved); //for now: lillis main

//dda
void	dda(t_raycast *ray, t_game *game);

//raycast_utils
void	set_plane(t_raycast *ray, t_game *game);
void	set_ray(t_raycast *ray, t_game *game, int i);
void	calc_wall_dist(t_raycast *ray, t_game *game);
void	calc_line_height(t_raycast *ray);

//texture utils
int		get_tex_color(int x, int y, t_texture_r *tex);
void	assign_tex(t_raycast *ray, t_game *game);
void	calc_texture_hit(t_raycast *ray, t_game *game);


//vector math
t_vector	norm_vector(double x, double y);
t_vector	v_change_len(double k, double x, double y);
t_vector	v_add(t_vector a, t_vector b);
double		vector_len(double x, double y);
t_vector	v_rotate(int degrees, t_vector a);

//player movement
int	boundary_check(t_vector *new, t_game *game); //TODO: check if any point on line next step = wall hit, not only end point (=going thru walls rn)
int change_orientation(int keycode, t_game *game); //change ->player->dir according to rotation matrix
void	move_w_s(int keycode, t_game *game);
void	move_a_d(int keycode, t_game *game);

//boundary
int	boundary_check(t_vector *new, t_game *game); //TODO: check if any point on line next step = wall hit, not only end point (=going thru walls rn)


//minimap
void	minimap(t_game *game);

//minimap utils
int count_map(char **map, int mode);
int	calc_square_size(int map_height, int map_width);


//utils
int		create_color(int t, int r, int g, int b);
void	my_mlx_pixel_put(t_img_r *data, int x, int y, int color);
int		get_map_point(int x,int y, t_game *game);
void	clear_image(t_game *game);

//hooks
void	hooks(t_game *game);
int		destroy_esc(int keycode, t_game *game);
int		quit_window(t_game *game);


#endif