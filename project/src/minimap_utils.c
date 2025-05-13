
#include "../includes/cub3d.h"


int count_map(char **map, int mode)
{
	int	i;

	if (mode == 1)
	{
		i = 0;
		while (map[0][i])
			i++;
	}
	else
	{
		i = 0;
		while (map[i])
			i++;
	}
	return (i);
}

int	calc_square_size(int map_height, int map_width)
{
	int square_size;
	(void) map_width;

	square_size = 18; //default size
	while ((map_height * square_size) > (0.3 * W_HEIGHT))
		square_size--;

	if (square_size == 0)
		square_size = 1;
	
	return (square_size);
}

