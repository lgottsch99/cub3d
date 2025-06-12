/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utilis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025-06-12 16:14:06 by selango           #+#    #+#             */
/*   Updated: 2025-06-12 16:14:06 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cub3d.h"
#include "../../includes/cub3d.h"


int	valid_extension(char *path, char *extension)
{
	size_t len_path;
	size_t ext_len;

	len_path = ft_strlen(path);
	ext_len = ft_strlen(extension);
	if (!path || !extension)
		return (0);
	else if (len_path >= ext_len && ft_strcmp(&path[len_path - ext_len],
			extension) == 0)
	{
		return (1);
	}
	return (0);
}

int	create_new_color(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

/* this function ensures that it is enclosed with the 1
	it checks for the boundary checks in the map
	checks all the 4 directions if it is not a space*/
int	is_map_enclosed(char **map, int height, int width)
{
	t_mapcheck val;

	val.i = 0;
	while (val.i < height)
	{
		val.j = 0;
		while (val.j < width)
		{
			val.c = map[val.i][val.j];
			if (!is_valid_char(val.c))
				return (0);
			if (val.c == '0' || ft_strchr("NSEW", val.c))
			{
				val.p.i = val.i;
				val.p.j = val.j;
				if (!map_enclosed_helper(map, val.p, height, width))
					return (0);
			}
			val.j++;
		}
		val.i++;
	}
	return (1);
}

int	single_player(char **map)
{
	int i;
	int j;
	int count;

	count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW", map[i][j]))
				count++;
			j++;
		}
		i++;
	}
	if (count != 1)
		return (0);
	return (1);
}

void	trim_crlf(char *line)
{
	char *p;

	p = line;
	while (*p)
	{
		if (*p == '\r' || *p == '\n')
		{
			*p = '\0';
			break ;
		}
		p++;
	}
}
