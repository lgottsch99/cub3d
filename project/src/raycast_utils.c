/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Watanudon <Watanudon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:11:44 by lgottsch          #+#    #+#             */
/*   Updated: 2025/05/13 10:34:08 by Watanudon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


int	get_tex_color(int x, int y, t_texture *tex)
{
	//printf("Getting tex color\n");
	int		color;
	char	*pix; //pointer to pix


	// Offset in Byte zu (x, y) berechnen
	pix = tex->data_addr + (y * tex->size_line + x * (tex->bpp / 8)); //calc pix address in mem

	// ARGB-Wert lesen (je nach Endian und bpp)
	color = *(unsigned int *)pix; //unsigned int bc color usually saved as 32 bit int
	
	return (color);
}

/* function drawing vertical line (wall)
*/
// void	draw_wall_line(t_game *game, int vertical_row, int draw_start, int draw_end, int color, int tex_x, t_texture *tex)
// {
// 	printf("in draw vertical line\n");
// 	int i;
// 	int color_ceiling;
// 	int color_floor;
// 	int line_height;
// 	int tex_y;
// 	int color_tex;
// 	(void)color;
	
// 	if (tex->data_addr == NULL) //OK
// 		printf("getting TEXTURE addr FAILED\n");

// 	line_height = draw_end - draw_start;
// 	color_ceiling = create_color(0, game->world->ceiling_r, game->world->ceiling_g, game->world->ceiling_b);
// 	color_floor = create_color(0, game->world->floor_r, game->world->floor_g, game->world->floor_b);
// 	printf("created floor ceiling color\n"); //OK

// 	double	tex_start; //starting y pos in texture (if smaller than og tex img, maybe offset)
// 	double	step; //factor of how many pixels to skip/add 
// 	//get tex_y for color to draw according to wall height
// 	printf("draw_start: %d, draw_end: %d, line_height: %d\n", draw_start, draw_end, line_height);
// 	printf("tex hieght; %i\n", tex->tex_height);
// 	printf("tex img; %p\n", tex->img);
// 	printf("tex data addr; %s\n", tex->data_addr);
// 	if (!tex || tex->img == NULL || tex->data_addr == NULL)
// 	{
// 		printf("Error: Texture data is not loaded properly.\n");
// 		return ;
// 	}
	
// 	step = (double)tex->tex_height / (double)line_height;
// 	printf("test1\n");
// 	tex_start = (draw_start - W_HEIGHT / 2 + line_height / 2) * step; //always taking middle of window as ref
// 	printf("calc step and tex start ok\n");

	
// 	i = 0;
// 	while(i < W_HEIGHT)
// 	{
// 		if (i >= 0 && i < draw_start) //ceiling
// 		{
// 			my_mlx_pixel_put(game->image, i, vertical_row, color_ceiling);
// 		}
// 		if (i >= draw_start && i <= draw_end)//wall
// 		{
// 				tex_y = (int)tex_start % tex->tex_height; //skale to tex height
// 				if (tex_start < 0)
// 					tex_start = 0;
// 				if (tex_start >= tex->tex_height)
// 					tex_start = tex->tex_height - 1;

// 				tex_y = (int)tex_start;
// 				tex_start += step;
// 				// tex_y = (int)tex_start % tex->tex_height;
// 				// tex_start += step;  // Update tex_start für den nächsten Pixel
// 				color_tex = get_tex_color(tex_x, tex_y, tex);
				
// 			//printf("putting pixel\n");
// 			my_mlx_pixel_put(game->image, i, vertical_row, color_tex);
// 		}
// 		if (i > draw_end) //floor
// 			my_mlx_pixel_put(game->image, i, vertical_row, color_floor);
// 		i++;
// 	}
// }

// void draw_wall_line(t_game *game, int vertical_row, int draw_start, int draw_end, int tex_x, t_texture *tex)
// {
//     // int i;
//     // int color_ceiling;
//     // int color_floor;
//     // int color_tex;
//     // int line_height;
//     // double step;
//     // double tex_pos;
//     // int tex_y;

//     // if (!tex || tex->data_addr == NULL)
//     // {
//     //     printf("Error: Texture not loaded.\n");
//     //     return;
//     // }

//     // color_ceiling = create_color(0, game->world->ceiling_r, game->world->ceiling_g, game->world->ceiling_b);
//     // color_floor = create_color(0, game->world->floor_r, game->world->floor_g, game->world->floor_b);
//     // //line_height = draw_end - draw_start;

//     // // How much to increase texture coordinate per screen pixel
//     // step = (double)tex->tex_height / (double)line_height;

//     // // Where on the texture to start
//     // double wall_top = draw_start;
//     // if (line_height > W_HEIGHT)
//     //     wall_top = (draw_start - (W_HEIGHT - line_height) / 2.0);

//     // tex_pos = step * (wall_top - draw_start);

//     // for (i = 0; i < W_HEIGHT; i++)
//     // {
//     //     if (i < draw_start)
//     //     {
//     //         my_mlx_pixel_put(game->image, i, vertical_row, color_ceiling);
//     //     }
//     //     else if (i >= draw_start && i <= draw_end)
//     //     {
//     //         tex_y = (int)tex_pos;
//     //         if (tex_y < 0)
//     //             tex_y = 0;
//     //         if (tex_y >= tex->tex_height)
//     //             tex_y = tex->tex_height - 1;

//     //         color_tex = get_tex_color(tex_x, tex_y, tex);
//     //         my_mlx_pixel_put(game->image, i, vertical_row, color_tex);
//     //         tex_pos += step;
//     //     }
//     //     else
//     //     {
//     //         my_mlx_pixel_put(game->image, i, vertical_row, color_floor);
//     //     }
//     // }
// 	return;
// }


// void draw_wall_line(t_game *game, int vertical_row, int draw_start, int draw_end, int color, int tex_x, t_texture *tex) {
//     printf("in draw vertical line\n");
//     int i;
//     int color_ceiling;
//     int color_floor;
//     int line_height;
//     int tex_y;
//     int color_tex;
//     (void)color;

//     if (tex->data_addr == NULL) {
//         printf("getting TEXTURE addr FAILED\n");
//     }

//     line_height = draw_end - draw_start;
//     color_ceiling = create_color(0, game->world->ceiling_r, game->world->ceiling_g, game->world->ceiling_b);
//     color_floor = create_color(0, game->world->floor_r, game->world->floor_g, game->world->floor_b);
//     printf("created floor ceiling color\n");

//     double tex_start; // starting y position in texture (if smaller than original texture size, maybe offset)
//     double step; // factor of how many pixels to skip/add
//     printf("draw_start: %d, draw_end: %d, line_height: %d\n", draw_start, draw_end, line_height);
//     printf("tex height; %i\n", tex->tex_height);
//     printf("tex img; %p\n", tex->img);
//     printf("tex data addr; %s\n", tex->data_addr);

//     if (!tex || tex->img == NULL || tex->data_addr == NULL) {
//         printf("Error: Texture data is not loaded properly.\n");
//         return;
//     }

//     // Perspective calculation for texture height scaling
//     step = (double)tex->tex_height / (double)line_height;
//     printf("test1\n");
//     tex_start = (draw_start - W_HEIGHT / 2 + line_height / 2) * step; // middle of the window as reference
//     printf("calc step and tex start ok\n");

//     i = 0;
//     while (i < W_HEIGHT) {
//         if (i >= 0 && i < draw_start) { // ceiling
//             my_mlx_pixel_put(game->image, i, vertical_row, color_ceiling);
//         }

//         if (i >= draw_start && i <= draw_end) { // wall
            
// 			// Ensure tex_start is within valid bounds
// 			if (tex_start < 0)
// 			tex_start = 0;
// 			if (tex_start >= tex->tex_height)
// 			tex_start = tex->tex_height - 1;
			
// 			// Calculate the vertical texture coordinate for this pixel
//             tex_y = (int)tex_start % tex->tex_height; // scale to texture height
//             tex_start += step;  // Update tex_start for the next pixel

//             // Apply the proper texture sampling
//             color_tex = get_tex_color(tex_x, tex_y, tex);
//             my_mlx_pixel_put(game->image, i, vertical_row, color_tex);
//         }

//         if (i > draw_end) { // floor
//             my_mlx_pixel_put(game->image, i, vertical_row, color_floor);
//         }

//         i++;
//     }
// }
