/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utilis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-05 11:04:03 by selango           #+#    #+#             */
/*   Updated: 2025-05-05 11:04:03 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	exit_error(char *str)
{
	printf("Error:%s\n", str);
	exit(EXIT_FAILURE);
}

int	str_digit(char *str)
{
	int	i;

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
void	free_2d_array(char **strs)
{
	while (*strs)
	{
		free(*strs);
		*strs++;
	}
}

void	assign_color(int i, char **strs, t_color *color)
{
	int	r;
	int	g;
	int	b;

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
	char	**ptr;

	if (!*strs)
	{
		*strs = ft_calloc(new_size, 1);
		if (*strs)
			return (NULL);
		return (*strs);
	}
	//todo the rest functions
}
