/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Watanudon <Watanudon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:17:07 by lgottsch          #+#    #+#             */
/*   Updated: 2025/04/29 20:56:42 by Watanudon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// LIBRARIES ----------------------------------

# include "../lib/full_libft/full_libft.h"
# include "../lib/mlx_linux/mlx.h" //minilibx for graphics rendering
# include "maps.h"
# include <fcntl.h> // file descriptor
# include <math.h>
# include <stdio.h>
# include <string.h>
//# include <X11/keysym.h> //defines some keycodes for hooks,

// for event macros like KeyPress
// https://codebrowser.dev/kde/include/X11/X.h.html
//#include <X.h> //needed on mac?

// MACROS ----------------------------------

// STRUCTS ----------------------------------

typedef struct s_game
{
	void			*mlx;
	void			*window;
	t_img			*image;
	t_map			*map;
	t_texture		No_texture;
	t_texture		So_texture;
	t_texture		We_texture;
	t_texture		Ea_texture;
	t_color			ceiling;
	t_color			floor;

}					t_game;

// FUNCTIONS ----------------------------------

#endif