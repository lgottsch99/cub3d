/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:53:13 by lgottsch          #+#    #+#             */
/*   Updated: 2025/05/17 14:39:38 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cub3d.h"

/* Ft calculating length of vector
for double : sqrt()
for float : sgrtf()
*/
double	vector_len(double x, double y)
{
	return(sqrt((x * x) + (y * y)));
}

/* Norming of a 2D vector (make its length = 1)
*/
t_vector	norm_vector(double x, double y)
{
	t_vector	normed;
	double		v_len; //len of vector

	v_len = vector_len(x, y);
	// divide each vector coord / len -> total len will be 1
	normed.x = x / v_len;
	normed.y = y / v_len;
	
	//printf("normed vetor check, len: %f\n", vector_len(normed.x, normed.y));
	return (normed);
}

/* Changing a vectors length to k
*/
t_vector	v_change_len(double k, double x, double y)
{
	t_vector	vector;
	if (vector_len(x, y) != 1.0) //norm if not yet
		vector = norm_vector(x, y);
	else
	{
		vector.x = x;
		vector.y = y;
	}
	//change len 
	vector.x = k * vector.x;
	vector.y = k * vector.y;
	//printf("resized vector check, len: %f\n", vector_len(vector.x, vector.y));

	return (vector);
}

/* Addition of 2 Vectors (A + B = start at point a and + b)
*/
t_vector	v_add(t_vector a, t_vector b)
{
	t_vector new_point;
	//add each coord
	new_point.x = a.x + b.x;
	new_point.y = a.y + b.y;

	// printf("addition new x: %f\n", new_point.x);
	// printf("addition new y: %f\n", new_point.y);
	return (new_point);
}

/*
Rotates vector a for degrees number of degrees AGAINST THE CLOCK
*/
t_vector	v_rotate(int degrees, t_vector a)
{
	t_vector	new;
	double	radiant;

	//change degrees into radians
	radiant = degrees * (M_PI / 180.0);
	//create rotation matrix + multip. matrix with vector
	new.x = a.x * cos(radiant) - a.y * sin(radiant);
	new.y = a.x * sin(radiant) + a.y * cos(radiant);

	return (new);
}