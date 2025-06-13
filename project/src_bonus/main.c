/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:41:25 by lgottsch          #+#    #+#             */
/*   Updated: 2025/06/13 16:46:01 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char *argv[])
{
	bool	moved;
	t_game	game;
	int		fd;

	moved = false;
	if (argc != 2 || !valid_cub_ext(argv[1]))
		exit_error("Enter the argument like ./cub3d map.cub", &game);
	printf("🟢 Starting main()\n");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit_error("Could not open the file", &game);
	printf("🟢 Calling parse_data()\n");
	parse_data(fd, &game);
	validate_game_data(&game);
	close(fd);
	raycasting_main(&game, &moved);
	return (0);
}
