/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_count                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-05 13:47:54 by selango           #+#    #+#             */
/*   Updated: 2025-05-05 13:47:54 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../full_libft.h"

int	ft_strchr_count(char *s, int c)
{
	int	count;

	count = 0;
	if (s == 0)
		return (0);
	while (*s)
	{
		if (*s == c)
			count++;
		s++;
	}
	return (count);
}
