/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcossett <rcossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:35:10 by rcossett          #+#    #+#             */
/*   Updated: 2025/02/13 17:20:13 by rcossett         ###   ########.fr       */
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
		free(ent->frames);
	}
	free(ent);
}

void	free_ents(t_game *game)
{
	int			i;

	i = -1;
	while (game->ents[++i])
		free_entity(game, game->ents[i]);
	free(game->ents);
}

void	free_map(t_game *game)
{
	int	i;

	i = -1;
	while (game->map[++i])
		free(game->map[i]);
	free(game->map);
}

// on itere dans les entites puis dans leurs
// potentielles afin de destroy image + free
void	free_and_exit(char *msg, t_game *game)
{
	if (game->ents != NULL)
		free_ents(game);
	if (game->map != NULL)
		free_map(game);
	if (game->bgr)
	{
		mlx_destroy_image(game->mlx, game->bgr);
		game->bgr = NULL;
	}
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (msg)
		printf("%s\n", msg);
	exit(0);
}
