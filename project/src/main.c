// Header

#include "../includes/cub3d.h"
#include "../includes/maps.h"


int	main(int argc, char **argv)
{
	int fd;
	t_game game;
	//checks the number of args.
	if (argc != 2)
		exit_error("Enter the argument like ./cub3d map.cub");
	//opens the map using the fd.
	fd = open(argv[1], O_RDONLY);
	if(fd < 0)
		exit_error("Could not open the file");
	//Parse the map values 
	parse_data(fd, &game);
	close(fd);
	return (0);
}