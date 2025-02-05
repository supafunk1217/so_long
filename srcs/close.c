/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcossett <rcossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 00:26:35 by rcossett          #+#    #+#             */
/*   Updated: 2025/01/23 02:16:29 by rcossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	free_entity(t_game *game, t_entity *ent)
{
	int	frame_index;

	if (ent->frames != NULL)
	{
		frame_index = -1;
		while (ent->frames[++frame_index])
			mlx_destroy_image(game->mlx, ent->frames[frame_index]);
	}
	free(ent);
}

void	free_entities(t_game *game)
{
	int			i;

	i = -1;
	while (game->entities[++i])
		free_entity(game, game->entities[i]);
	free(game->entities);
}

void	free_map(t_game *game)
{
	int	i;

	i = -1;
	while (game->map[++i])
		free(game->map[i]);
	free(game->map);
}

// on itere dans les entites puis dans leurs frames potentielles afin de destroy image + free
void	free_and_exit(t_game *game)
{
	free_entities(game);
	free_map(game);
	mlx_destroy_image(game->mlx, game->bgr);
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}
