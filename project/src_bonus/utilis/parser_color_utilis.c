/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color_utilis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:49:18 by selango           #+#    #+#             */
/*   Updated: 2025/06/13 16:15:40 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*trim_whitespaces(char *str)
{
	char	*trimmed_value;

	trimmed_value = ft_strtrim(str, " \n\t\r");
	if (!trimmed_value)
	{
		return (NULL);
	}
	return (trimmed_value);
}

int	validate_single_color(char **strs)
{
	int		i;
	char	*trimmed;

	i = 0;
	while (strs[i] != 0)
	{
		trimmed = trim_whitespaces(strs[i]);
		if (!trimmed)
			return (0);
		else if (!str_digit(trimmed))
		{
			free(trimmed);
			return (0);
		}
		free(strs[i]);
		strs[i] = trimmed;
		i++;
	}
	return (1);
}
