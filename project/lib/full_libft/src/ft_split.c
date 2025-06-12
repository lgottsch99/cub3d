/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:07:52 by lgottsch          #+#    #+#             */
/*   Updated: 2024/11/15 17:40:42 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../full_libft.h"

/*
Allocates (with malloc(3)) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter.  The array must end
with a NULL pointer.

use: malloc, free

return: The array of new strings resulting from the split.
NULL if the allocation fails.
*/

int ft_is_delim(char c, char *delimiters)
{
	while(*delimiters)
	{
		if(c == *delimiters)
			return(1);
		delimiters++;
	}
	return(0);
}

static int	ft_words(char const *s, char *delimiter)
{
	int	words;
	int	control;
	int	i;

	i = 0;
	control = 0;
	words = 0;
	while (s[i])
	{
		if (!ft_is_delim(s[i], delimiter) && control == 0)
		{
			words++;
			control = 1;
		}
		else if (ft_is_delim(s[i],delimiter))
			control = 0;
		i++;
	}
	return (words);
}

static int	ft_sep(char const *s, char *delimiter, int i)
{
	int	y;

	y = 0;
	while (s[i + y] && !ft_is_delim(s[i + y],delimiter))
		y++;
	return (y);
}

static void	*ft_free_all(char **array, int x)
{
	int	i;

	i = 0;
	while (i <= x)
	{
		free(array[i]);
		i++;
	}
	return(NULL);
}

char	**ft_split(char const *s, char *delimiters)
{
	char	**array;
	int		i;
	char	*ptr;
	int		x;

	array = (char **)malloc(sizeof(char *) * (ft_words(s, delimiters) + 1));
	if (!array)
		return (NULL);
	i = 0;
	x = 0;
	while (s[i])
	{
		if (ft_is_delim(s[i],delimiters))
			i++;
		else
		{
			ptr = ft_substr(s, i, ft_sep(s, delimiters, i));
			if (!ptr)
				return (ft_free_all(array, x));
			array[x++] = ptr;
			i = i + ft_sep(s, delimiters, i);
		}
	}
	array[x] = NULL;
	return (array);
}
