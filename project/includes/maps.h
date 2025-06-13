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

typedef struct s_game	t_game;

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
// it converts the r,g,b into a one color
typedef struct s_color
{
	int		r;
	int		g;
	int		b;
	int		full_color;
}			t_color;
// texture on the walls struct
typedef struct s_texture
{
	char	*path;
	int		tex_width;
	int		tex_height;
}			t_texture;

typedef struct s_pos
{
	int		i;
	int		j;
}	t_pos;

typedef struct s_mapcheck
{
	int		i;
	int		j;
	char	c;
	t_pos	p;
}		t_mapcheck;

typedef struct s_store_map
{
	char *single_value;
	int count;
	int fd;
	char *line;
	char **grid;
} t_store_map;

typedef struct s_process_line
{
	char	*trimmed;
	char	*id;
	char	*value;
	char	**strs;
} t_process_line;

// functions
/* parsing map */
int			valid_cub_ext(char *path);
void		init_game(t_game *game);
int			init_data(char **strs, t_game *game);
char		*get_word(char *line);
int			ft_isspace(char c);
char		**process_str(char *id, char *value);
// void		process_line(char *line, t_game *game, char **realline);
int		process_line(char *line, t_game *game);

void		print_map(t_map *map);
void		print_map_normalize(int height, char **map);
void		parse_data(int fd, t_game *game);
// void		parse_texture(char *text_path, t_texture *texture);
int			parse_texture(char *text_path, t_texture *texture, t_game *game);
int			validate_single_color(char **strs);
int			parse_color(char *value, t_color *color);
int			valid_map(char *grid);
// void		handle_invalid_map(t_map *map);
void		handle_invalid_map(t_map *map, t_game *game);
char		**handle_different_map(t_map *map, int expected_width,
				int *new_width);
void		store_map(int fd, char *line, t_map *map);
size_t		map_width(char **grid);
size_t		map_height(char **grid);
void		entire_map(int fd, char *line, t_map *map);
// void		exit_error(char *str);
void		free_2d_array(char **strs);
int			str_digit(char *str);
void		assign_color(int i, char **strs, t_color *color);
char		**correct_map(char **strs, int width, int height);
void		tab_check(char *strs, int *len);
void		*ft_realloc_str(void **strs, size_t old_size, size_t new_size);
char		*trim_whitespaces(char *str);
int			store_map_utilis(int fd, char *line, char **grid);

//validate the data
int			valid_extension(char *path, char *extension);
void		validate_game_data(t_game *game);
// void		validate_color(t_color *color, char *side_name);
void		validate_color(t_color *color, char *side_name, t_game *game);
int			create_new_color(int a, int r, int g, int b);
int			is_valid_char(char c);
int			map_enclosed_helper(char **map, t_pos p, int height, int width);
int			is_map_enclosed(char **map, int height, int width);
int			single_player(char **map);
void		assign_map(char **map, int correct_width, char **new_map, int i);
char		**normalize_map(char **map, int height, int *out_width);
int			is_rectangular(char **map, int height, int expected_width);
void		free_map_to_validate(char **grid, char **map);
int			max_width(char **map, int height);
void		trim_crlf(char *line);
// void		validate_map(t_map *map);
void		validate_map(t_map *map, t_game *game);
void		free_game(t_game *game);
void		free_process_line(char *trimmed, char *value,
				char *id, char **strs);
//helpers

void	init_struct(t_store_map *m, int fd, char *line, char **grid);
int		is_line_empty(char *line);
void	store_more_map(t_store_map *m);
void	print_map(t_map *map);
void	error_parsing(t_game *game, char *line, int fd);

#endif
