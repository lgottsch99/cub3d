/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-12 11:34:18 by selango           #+#    #+#             */
/*   Updated: 2025-06-12 11:34:18 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*trimmed ---> trim the spaces in the line.
get the first word ---> using the id
Get the rest of the line after the identifier----> using value
Im USING 3 FOR str[0],str[1], null operator*/
int	process_line(char *line, t_game *game)
{
	t_process_line	p;

	p.trimmed = trim_whitespaces(line);
	if (!p.trimmed || p.trimmed[0] == '\0')
		return (free(p.trimmed), 0);
	p.id = get_word(p.trimmed);
	if (!p.id)
		return (free(p.trimmed), 0);
	p.value = p.trimmed + ft_strlen(p.id);
	while (*p.value && ft_isspace(*p.value))
		p.value++;
	p.value = ft_strdup(p.value);
	if (!p.value)
		return (free(p.id), free(p.trimmed), 0);
	p.strs = process_str(p.id, p.value);
	if (!p.strs)
		return (free(p.id), free(p.trimmed), free(p.value), 0);
	if (init_data(p.strs, game) == 1)
	{
		free_process_line(p.trimmed, p.value, p.id, p.strs);
		return (-1);
	}
	free_process_line(p.trimmed, p.value, p.id, p.strs);
	return (0);
}

char	*get_word(char *line)
{
	int	i;

	i = 0;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	return (ft_substr(line, 0, i));
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\f'
		|| c == '\r');
}

char	**process_str(char *id, char *value)
{
	char	**strs;

	strs = malloc(sizeof(char *) * 3);
	if (!strs)
		return (NULL);
	strs[0] = ft_strdup(id);
	strs[1] = ft_strdup(value);
	strs[2] = NULL;
	if (!strs[0] || !strs[1])
	{
		free(strs[0]);
		free(strs[1]);
		free(strs);
		return (NULL);
	}
	return (strs);
}
