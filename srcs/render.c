/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcossett <rcossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:27:25 by rcossett          #+#    #+#             */
/*   Updated: 2025/02/12 21:57:16 by rcossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// renders only the ents which type is equal to the
// type passed as argument, giving us control on the order of rendering
void	render_ent(t_game *game, t_entity *ent)
{
	mlx_put_image_to_window(game->mlx, game->win, \
		ent->current_frame, ent->pos.x, ent->pos.y);
}

// fonction for defining if type on tile is active
void	render_type(t_game *game, t_entity_type type)
{
	int	i;

	i = 0;
	while (game->ents[i])
	{
		if (type == exitance && game->collectibles < game->max_collectibles)
			break ;
		if (game->ents[i]->type == type && game->ents[i]->active == 1)
			render_ent(game, game->ents[i]);
		i++;
	}
}

void	render_ents(t_game *game)
{
	t_entity	bgr;

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
	render_ents(game);
}
