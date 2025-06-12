/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utilis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-12 15:55:52 by selango           #+#    #+#             */
/*   Updated: 2025-06-12 15:55:52 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cub3d.h"
#include "../../includes/cub3d.h"

/*This function helps to find the max_width required for the normalize map*/
int	max_width(char **map, int height)
{
	int	i;
	int	width;
	int	len;

	i = 0;
	width = 0;
	while (i < height)
	{
		len = ft_strlen(map[i]);
		if (len > width)
			width = len;
		i++;
	}
	return (width);
}

int	len_check_for_rect(char *line)
{
	int	len;

	if (!line)
		return (0);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == ' ')
		len--;
	return (len);
}

int	is_rectangular(char **map, int height, int expected_width)
{
	int	i;

	i = 0;
	while (i < height)
	{
		if (len_check_for_rect(map[i]) != expected_width)
			return (0);
		i++;
	}
	return (1);
}

char	**normalize_map(char **map, int height, int *out_width)
{
	char	**new_map;
	int		correct_width;
	int		i;

	correct_width = max_width(map, height);
	i = 0;
	new_map = malloc(sizeof(char *) * (height + 1));
	if (!new_map)
		return (NULL);
	while (i < height)
	{
		new_map[i] = malloc(correct_width + 1);
		if (!new_map[i])
		{
			free_2d_array(new_map);
			return (NULL);
		}
		assign_map(map, correct_width, new_map, i);
		i++;
	}
	new_map[height] = NULL;
	*out_width = correct_width;
	return (new_map);
}

void	assign_map(char **map, int correct_width, char **new_map, int i)
{
	int	j;

	j = 0;
	while (map[i][j])
	{
		new_map[i][j] = map[i][j];
		j++;
	}
	while (j < correct_width)
		new_map[i][j++] = ' ';
	new_map[i][correct_width] = '\0';
}
