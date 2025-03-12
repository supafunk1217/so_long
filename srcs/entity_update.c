/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcossett <rcossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:40:00 by rcossett          #+#    #+#             */
/*   Updated: 2025/03/12 22:31:45 by rcossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// condition anti flickering pour trigger le render de maniere minimale
void	update_player(t_game *game, t_entity *plr)
{
	t_entity	*ent;

	ent = get_ent_at_position(game, game->player->pos, game->player);
	if (ent && ent->type == enemy)
		free_and_exit("WTF YOU COMMITED SUICIDE", game);
	if (ent && ent->type == collectible)
	{
		printf("Item count: %i\n", game->collectibles);
		ent->active = 0;
		game->collectibles++;
	}
	else if (ent && ent->type == exitance && \
		game->collectibles == game->max_collectibles)
		free_and_exit("Glorious victory ! Thanks for playing.", game);
	if (plr->pos.x != plr->start_pos.x || plr->pos.y != plr->start_pos.y)
	{
		render_game(game);
		plr->start_pos = get_v2(plr->pos.x, plr->pos.y);
	}
}

void	update_ents(t_game *game)
{
	int	i;
	int	should_render;

	should_render = 0;
	i = 0;
	while (game->ents[i])
	{
		if (game->ents[i]->type == enemy)
			if (update_enemy(game, game->ents[i], i))
				should_render = 1;
		i++;
	}
	if (should_render || game->time <= 5)
		render_game(game);
}

int	update(t_game *game)
{
	update_ents(game);
	update_player(game, game->player);
	game->time++;
	return (0);
}
