/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:41:25 by lgottsch          #+#    #+#             */
/*   Updated: 2025/05/04 13:42:35 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


int	main(void)
{
	t_game	game; //big main struct
	
	printf("hello\n");
	// 0 input validation

	// 1 map initialization + window creation
	
	// 2 casting the rays
	raycasting_main(&game);
	
	// 3 rendering walls
	
	// 4 player movement
	
	return (0);
}