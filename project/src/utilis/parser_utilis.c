/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utilis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025-05-05 11:04:03 by selango           #+#    #+#             */
/*   Updated: 2025-05-05 11:04:03 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/cub3d.h"
#include "../../includes/cub3d.h"

void	exit_error(char *str)
{
	printf("Error:%s\n", str);
	exit(EXIT_FAILURE);
}

int	str_digit(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	assign_color(int i, char **strs, t_color *color)
{
	int r;
	int g;
	int b;

	r = 0;
	g = 0;
	b = 0;
	if (i == 3)
	{
		r = ft_atoi(strs[0]);
		g = ft_atoi(strs[1]);
		b = ft_atoi(strs[2]);
	}
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return ;
	color->r = r;
	color->g = g;
	color->b = b;
}
/*This function creates a mem and then allocates the string to a new string*/
void	*ft_realloc_str(void **strs, size_t old_size, size_t new_size)
{
	char *ptr;
	/*if the ptr is null . it allocates the mem for the ptr and then return the pointer*/
	if (!*strs)
	{
		*strs = ft_calloc(new_size, 1);
		if (!*strs)
			return (NULL);
		return (*strs);
	}
	/*It checks if the new_size is lesser then it return the ptr*/
	if (new_size <= old_size)
		return (*strs);
	ptr = ft_calloc(new_size, 1);
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, (char *)*strs, old_size);
	free(*strs);
	*strs = ptr;
	ptr = NULL;
	return (*strs);
}

int	store_map_utilis(int fd, char *line, char **grid)
{
	char *single_value;
	int count;
	
	single_value = line;
	count = 0;
	while (single_value && count < MAX_LINES)
	{
		grid[count] = ft_strdup(single_value);
		if (!grid[count])
		{
			int i;
			i = 0;
			while (i < count)
			{
				free(grid[i]);
				i++;
			}
			return (-1);
		}
		trim_crlf(grid[count]);
		count++;
		if (single_value != line)
			free(single_value);
		single_value = get_next_line(fd);
	}
	grid[count] = NULL;
	return (0);
}
