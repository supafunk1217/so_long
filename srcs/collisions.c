/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcossett <rcossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 00:33:54 by rcossett          #+#    #+#             */
/*   Updated: 2025/02/13 18:21:32 by rcossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	is_move_valid(t_game *game, t_vec2 new_pos)
{
	int	i;

	i = -1;
	while (game->ents[++i])
	{
		if (game->ents[i]->type == wall && \
			cmp_vec2(game->ents[i]->pos, new_pos))
			return (0);
	}
	return (1);
}

t_entity	*get_ent_at_position(t_game *game, t_vec2 pos, t_entity *me)
{
	int	i;

	i = -1;
	while (game->ents[++i])
	{
		if (!game->ents[i]->active || game->ents[i] == me)
			continue ;
		if (cmp_vec2(game->ents[i]->pos, pos))
			return (game->ents[i]);
	}
	return (NULL);
}
