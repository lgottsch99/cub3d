/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:41:25 by lgottsch          #+#    #+#             */
/*   Updated: 2025/05/16 18:52:33 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


int	main(void)
{
	bool	moved;
	t_game	game; //big main struct
	
	moved = false;
	printf("hello\n");
	// 0 input validation

	// 1 map initialization + window creation
	
	// 2 casting the rays
	raycasting_main(&game, &moved);
	
	// 3 rendering walls
	
	// 4 player movement
	
	return (0);
}