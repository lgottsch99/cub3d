/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:11:59 by lgottsch          #+#    #+#             */
/*   Updated: 2025/06/13 16:14:37 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

//returns 0 if line is not empty, 1 if empty
int	is_line_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n'
			&& line[i] != '\r' && line[i] != '\v' && line[i] != '\f')
			return (0);
		i++;
	}
	return (1);
}

void	init_struct(t_store_map *m, int fd, char *line, char **grid)
{
	m->single_value = NULL;
	m->count = 0;
	m->fd = fd;
	m->line = line;
	m->grid = grid;
}

void	store_more_map(t_store_map *m)
{
	trim_crlf(m->grid[m->count]);
	m->count++;
	if (m->single_value != m->line)
		free(m->single_value);
	m->single_value = get_next_line(m->fd, 0);
}
