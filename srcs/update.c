/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcossett <rcossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:21:10 by rcossett          #+#    #+#             */
/*   Updated: 2025/02/05 18:54:16 by rcossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	set_enemy_direction(t_entity *target, t_entity *ent)
{
	int	dx;
	int	dy;

	dx = target->pos.x - ent->pos.x;
	dy = target->pos.y - ent->pos.y;
	if (abs(dx) > abs(dy) && r_range(0, 5) != 0)
	{
		if (dx > 0)
			ent->direction = right; // L'ennemi se déplace vers la droite
		else
			ent->direction = left;  // L'ennemi se déplace vers la gauche
	}
	else
	{
		if (dy > 0)
			ent->direction = down;  // L'ennemi se déplace vers le bas
		else
			ent->direction = up;	// L'ennemi se déplace vers le haut
	}
}
int	update_enemy(t_game *game, t_entity *ent, int index)
{
	t_vec2	new_move_increment;

	(void)index;

	set_enemy_direction(game->player,  ent);
	if (game->time % (ENEMY_SPEED) == 0) // operation pour definir le moment ou l'ennemi va bouger
	{
		new_move_increment = get_v2(0, 0);
		if (ent->direction == up && is_move_valid(game, get_v2(ent->pos.x, \
				ent->pos.y - TILE_SIZE)))
			new_move_increment.y = -TILE_SIZE;
		else if (ent->direction == down && \
			is_move_valid(game, get_v2(ent->pos.x, ent->pos.y + TILE_SIZE)))
			new_move_increment.y = TILE_SIZE;
		else if (ent->direction == left && \
			is_move_valid(game, get_v2(ent->pos.x - TILE_SIZE, ent->pos.y)))
			new_move_increment.x = -TILE_SIZE;
		else if (ent->direction == right && \
			is_move_valid(game, get_v2(ent->pos.x + TILE_SIZE, ent->pos.y)))
			new_move_increment.x = TILE_SIZE;
		if (new_move_increment.x || new_move_increment.y)
		{
			ent->pos = get_v2(ent->pos.x + new_move_increment.x, \
				ent->pos.y + new_move_increment.y);
			return (1);
		}
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

void	update_player(t_game *game)
{
	t_entity	*ent;

	ent = get_ent_at_position(game, game->player->pos, game->player);
	if (ent && ent->type == collectible)
	{
		printf("Item count: %i\n", game->collectibles);
		ent->active = 0;
		game->collectibles++;
	}
	else if (ent && ent->type == exitance && game->collectibles == game->max_collectibles)
	{
		printf("Splendid victory ! Thanks for playing.\n");
		exit(0);
	}
	if (ent && ent->type == enemy)
	{
		printf("YOU DIED NOOB\n");
		free_and_exit(game);
	}
	if (game->player->pos.x != game->player->start_pos.x || game->player->pos.y != game->player->start_pos.y) // condition anti flickering pour trigger ler render de maniere minimale
	{
		render_game(game);
		game->player->start_pos = get_v2(game->player->pos.x, game->player->pos.y);
	}
}

void	update_entities(t_game *game)
{
	int	i;
	int	should_render;

	should_render = 0;
	i = 0;
	while (game->entities[i])
	{
		if (game->entities[i]->type == enemy)
			if (update_enemy(game, game->entities[i], i))
				should_render = 1;
		i++;
	}
	if (should_render)
		render_game(game);
}

// time % 500 = reste de time / 500
int	update(t_game *game)
{ 
	update_entities(game);
	update_player(game);
	game->time++;
	return (0);
}
