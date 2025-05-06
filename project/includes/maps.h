/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-05 10:59:06 by selango           #+#    #+#             */
/*   Updated: 2025-05-05 10:59:06 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPS_H
# define MAPS_H
# include "cub3d.h"
# define MAX_LINES 1000

// struct for  windows_mlx windows
typedef struct s_img
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		bpp;
	int		endian;
	int		line_length;
}			t_img;

// maps structure which has a grid view , width, and height
typedef struct s_map
{
	char	**map;
	int		map_width;
	int		map_height;
}			t_map;

// color of the floor and ceiling
typedef struct s_color
{
	int		r;
	int		g;
	int		b;
	int full_color; // it converts the r,g,b into a one color
}			t_color;
// texture on the walls struct
typedef struct s_texture
{
	char	*path;
	int		tex_width;
	int		tex_height;
}			t_texture;

// functions
/* parsing map */
void		init_game(t_game *game);
void		check_data(char **strs, t_game *game);
void		parse_texture(char *text_path, t_texture *texture);
void		parse_color(char *value, t_color *color);
int			valid_map(char *grid);

void		exit_error(char *str);
void		free_2d_array(char **strs);
int			str_digit(char *str);

#endif
