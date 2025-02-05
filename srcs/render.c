/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcossett <rcossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:27:25 by rcossett          #+#    #+#             */
/*   Updated: 2025/01/23 02:09:00 by rcossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

//		renders only the entities which type is equal to the type passed as argument, giving us control on the order of rendering

void	render_ent(t_game *game, t_entity *ent)
{
	t_vec2	offset;

	offset = get_v2((game->win_size.x / 2) - TILE_SIZE * (game->map_size.x / 2), \
	(game->win_size.y / 2) - TILE_SIZE * (game->map_size.y / 2));

	if (WIN_W_RATIO <= 1)
		offset.x = 0;
	if (WIN_H_RATIO <= 1)
		offset.y = 0;
	mlx_put_image_to_window(game->mlx, game->win, ent->current_frame, \
				ent->pos.x + offset.x, \
				ent->pos.y + offset.y);
}

void	render_type(t_game *game, t_entity_type type) // fonction for defining if type on tile is active
{
	int	i;

	i = 0;
	while (game->entities[i])
	{
		if (type == exitance && game->collectibles < game->max_collectibles)
			break ;
		if (game->entities[i]->type == type && game->entities[i]->active == 1)
			render_ent(game, game->entities[i]);
		i++;
	}
}

void	render_entities(t_game *game)
{
	t_entity bgr;

	bgr.pos = get_v2(-game->bgr_size.x / 3, -game->bgr_size.y / 3);
	bgr.current_frame = game->bgr;
	render_ent(game, &bgr);
	render_type(game, collectible);
	render_type(game, wall);
	render_type(game, exitance);
	render_type(game, enemy);
	render_ent(game, game->player);
}


void	render_game(t_game *game)
{
	render_entities(game);
}
