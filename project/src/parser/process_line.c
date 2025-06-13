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

// #include "cub3d.h"
#include "../../includes/cub3d.h"

/*trimmed ---> trim the spaces in the line.
get the first word ---> using the id
Get the rest of the line after the identifier----> using value
Im USING 3 FOR str[0],str[1], null operator*/
// void	process_line(char *line, t_game *game, char **realline)
// {
// 	char	*trimmed;
// 	char	*id;
// 	char	*value;
// 	char	**strs;

// 	trimmed = trim_whitespaces(line);
// 	if (!trimmed || trimmed[0] == '\0')
// 		return (free(trimmed));
// 	id = get_word(trimmed);
// 	if (!id)
// 		return (free(trimmed));
// 	value = trimmed + ft_strlen(id);
// 	while (*value && ft_isspace(*value))
// 		value++;
// 	value = ft_strdup(value);
// 	if (!value)
// 		return (free(id), free(trimmed));
// 	strs = process_str(id, value);
// 	if (!strs)
// 		return (free(id), free(trimmed), free(value));
// 	if (init_data(strs, game) == 1) //make init data return 1 in case of error, then free everything
// 	{
// 		printf("error after init data\n");
// 		free_process_line(trimmed, value, id, strs);
// 		free(*realline);
// 		line = NULL;
// 		free_everything(game, 1); //exit
// 	}
// 	free_process_line(trimmed, value, id, strs);
// }

int process_line(char *line, t_game *game)
{
	char *trimmed, *id, *value, **strs;

	trimmed = trim_whitespaces(line);
	if (!trimmed || trimmed[0] == '\0')
		return (free(trimmed), 0);
	id = get_word(trimmed);
	if (!id)
		return (free(trimmed), 0);
	value = trimmed + ft_strlen(id);
	while (*value && ft_isspace(*value))
		value++;
	value = ft_strdup(value);
	if (!value)
		return (free(id), free(trimmed), 0);
	strs = process_str(id, value);
	if (!strs)
		return (free(id), free(trimmed), free(value), 0);
	if (init_data(strs, game) == 1)
	{
		printf("error after init data\n");
		free_process_line(trimmed, value, id, strs);
		return -1;
	}
	free_process_line(trimmed, value, id, strs);
	return 0;
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
