/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:53:13 by lgottsch          #+#    #+#             */
/*   Updated: 2025/06/12 20:49:20 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Ft calculating length of vector
for double : sqrt()
for float : sgrtf()
*/
double	vector_len(double x, double y)
{
	return (sqrt((x * x) + (y * y)));
}

/* Norming of a 2D vector (make its length = 1)
divide each vector coord / len -> total len will be 1
*/
t_vector	norm_vector(double x, double y)
{
	t_vector	normed;
	double		v_len;

	v_len = vector_len(x, y);
	normed.x = x / v_len;
	normed.y = y / v_len;
	return (normed);
}

/* Changing a vectors length to k
*/
t_vector	v_change_len(double k, double x, double y)
{
	t_vector	vector;

	if (vector_len(x, y) != 1.0)
		vector = norm_vector(x, y);
	else
	{
		vector.x = x;
		vector.y = y;
	}
	vector.x = k * vector.x;
	vector.y = k * vector.y;
	return (vector);
}

/* Addition of 2 Vectors (A + B = start at point a and + b)
*/
t_vector	v_add(t_vector a, t_vector b)
{
	t_vector	new_point;

	new_point.x = a.x + b.x;
	new_point.y = a.y + b.y;
	return (new_point);
}

/*
Rotates vector a for degrees number of degrees AGAINST THE CLOCK
1.change degrees into radians
2.create rotation matrix + multip. matrix with vector
*/
t_vector	v_rotate(int degrees, t_vector a)
{
	t_vector	new;
	double		radiant;

	radiant = degrees * (M_PI / 180.0);
	new.x = a.x * cos(radiant) - a.y * sin(radiant);
	new.y = a.x * sin(radiant) + a.y * cos(radiant);
	return (new);
}
