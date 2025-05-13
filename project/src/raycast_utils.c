/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Watanudon <Watanudon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:11:44 by lgottsch          #+#    #+#             */
/*   Updated: 2025/05/13 13:19:33 by Watanudon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* getting color value at pixel x,y in texture
*/
int	get_tex_color(int x, int y, t_texture *tex)
{
	int		color;
	char	*pix; //pointer to pix

	//calc pix address in mem
	pix = tex->data_addr + (y * tex->size_line + x * (tex->bpp / 8));

	//unsigned int bc color usually saved as 32 bit int
	color = *(unsigned int *)pix;
	return (color);
}

