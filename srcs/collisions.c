/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcossett <rcossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 00:33:54 by rcossett          #+#    #+#             */
/*   Updated: 2025/01/23 02:17:06 by rcossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	is_move_valid(t_game *game, t_vec2 new_pos)
{
	int	i;

	i = -1;
	while (game->entities[++i])
	{
		if ((game->entities[i]->type == wall || game->entities[i]->type == enemy) && \
			cmp_vec2(game->entities[i]->pos, new_pos))
			return (0); // move is NOT valid
	}
	return (1); // move is valid but
}

t_entity	*get_ent_at_position(t_game *game, t_vec2 pos, t_entity *me)
{
	int	i;

	i = -1;
	while (game->entities[++i])
	{
		if (!game->entities[i]->active || game->entities[i] == me)
			continue ;
		if (cmp_vec2(game->entities[i]->pos, pos))
			return (game->entities[i]);
	}
	return (NULL);
}
