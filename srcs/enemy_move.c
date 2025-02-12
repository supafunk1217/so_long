/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcossett <rcossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:41:38 by rcossett          #+#    #+#             */
/*   Updated: 2025/02/12 21:46:01 by rcossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

//		direction de l'ennemi
void	set_enemy_direction(t_entity *target, t_entity *ent)
{
	int	dx;
	int	dy;

	dx = target->pos.x - ent->pos.x;
	dy = target->pos.y - ent->pos.y;
	if (abs(dx) > abs(dy) && r_range(0, 5) != 0)
	{
		if (dx > 0)
			ent->direction = right;
		else
			ent->direction = left;
	}
	else
	{
		if (dy > 0)
			ent->direction = down;
		else
			ent->direction = up;
	}
}

static int	handle_enemy_movement(t_game *game, t_entity *ent)
{
	t_vec2	new_move_increment;

	new_move_increment = get_v2(0, 0);
	if (ent->direction == up && \
		is_move_valid(game, get_v2(ent->pos.x, ent->pos.y - game->tile_size)))
		new_move_increment.y = -game->tile_size;
	else if (ent->direction == down && \
		is_move_valid(game, get_v2(ent->pos.x, ent->pos.y + game->tile_size)))
		new_move_increment.y = game->tile_size;
	else if (ent->direction == left && \
		is_move_valid(game, get_v2(ent->pos.x - game->tile_size, ent->pos.y)))
		new_move_increment.x = -game->tile_size;
	else if (ent->direction == right && \
		is_move_valid(game, get_v2(ent->pos.x + game->tile_size, ent->pos.y)))
		new_move_increment.x = game->tile_size;
	if (new_move_increment.x || new_move_increment.y)
	{
		ent->pos = get_v2(ent->pos.x + new_move_increment.x, \
						ent->pos.y + new_move_increment.y);
		return (1);
	}
	return (0);
}

// operation pour definir le moment ou l'ennemi va bouger
int	update_enemy(t_game *game, t_entity *ent, int index)
{
	(void)index;
	set_enemy_direction(game->player, ent);
	if (game->time % (ENEMY_SPEED) == 0)
	{
		if (handle_enemy_movement(game, ent))
			return (1);
	}
	if (game->time % ANIM_REFRESH == 0)
	{
		ent->frame_index++;
		if (!ent->frames[ent->frame_index])
			ent->frame_index = 0;
		ent->current_frame = ent->frames[ent->frame_index];
		return (1);
	}
	return (0);
}
