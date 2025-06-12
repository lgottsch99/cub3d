/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boundary_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:06:39 by lgottsch          #+#    #+#             */
/*   Updated: 2025/06/12 21:51:42 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* b->step = interval to check boundary 
*/
static void	calc_steps(t_vector *new, t_game *game, t_boundary *b)
{
	double	dx;
	double	dy;
	double	distance;

	b->step = 0.0000001;
	dx = new->x - game->player->pos_x;
	dy = new->y - game->player->pos_y;
	distance = vector_len(dx, dy);
	b->amount_steps = (int)(distance / b->step);
	if (b->amount_steps < 1)
		b->amount_steps = 1;
	b->x_step = dx / b->amount_steps;
	b->y_step = dy / b->amount_steps;
}

static void	assign_min_max(t_boundary *b)
{
	b->min_x = (int)trunc(b->x - b->player_radius);
	b->max_x = (int)trunc(b->x + b->player_radius);
	b->min_y = (int)trunc(b->y - b->player_radius);
	b->max_y = (int)trunc(b->y + b->player_radius);
}

static int	inner_b_loop(t_boundary *b, t_game *game)
{
	int	radius_y;
	int	radius_x;

	assign_min_max(b);
	radius_y = b->min_y;
	while (radius_y <= b->max_y)
	{
		radius_x = b->min_x;
		while (radius_x <= b->max_x)
		{
			if (get_map_point(radius_y, radius_x, game) == 1)
			{
				printf("Move would go inside wall! at tile (");
				printf("%d,%d)-> Not allowing\n", radius_x, radius_y);
				return (1);
			}
			radius_x++;
		}
		radius_y++;
	}
	b->x += b->x_step;
	b->y += b->y_step;
	return (0);
}

int	boundary_check(t_vector *new, t_game *game)
{
	t_boundary	b;
	int			i;

	calc_steps(new, game, &b);
	b.player_radius = PLAYER_RADIUS;
	b.x = game->player->pos_x;
	b.y = game->player->pos_y;
	i = 0;
	while (i <= b.amount_steps)
	{
		if (inner_b_loop(&b, game) == 1)
			return (1);
		i++;
	}
	return (0);
}
