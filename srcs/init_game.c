/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcossett <rcossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:24:32 by rcossett          #+#    #+#             */
/*   Updated: 2025/02/13 18:39:08 by rcossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/*static int is_safe_spawn_distance(t_game *game, t_vec2 pos)
{
	int	i;
	int	safe_distance;

	safe_distance = 2 * game->tile_size;
	i = -1;
	while (game->ents[++i])
	{
		if (abs(game->ents[i]->pos.x - pos.x) < safe_distance && 
			abs(game->ents[i]->pos.y - pos.y) < safe_distance)
			return (0);
	}
	return (1);
}*/

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit(EXIT_FAILURE);
	game->win = NULL;
	game->map_size = get_v2(0, 0);
	game->ents = NULL;
	game->player = NULL;
	game->map = NULL;
	game->moves = 0;
	game->collectibles = 0;
	game->max_collectibles = 0;
	game->initialized = 0;
	game->time = 0;
	game->bgr = NULL;
	game->bgr = mlx_xpm_file_to_image(game->mlx, BGR_IMG, \
		&game->bgr_size.x, &game->bgr_size.y);
	if (!game->bgr)
		free_and_exit("Error\n", game->mlx);
}

void	init_hooks(t_game *game)
{
	mlx_loop_hook(game->mlx, update, (void *)game);
	mlx_hook(game->win, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->win, X_EVENT_EXIT, 0, handle_close, game);
	mlx_loop(game->mlx);
}

static void	process_entity(t_game *game, int *ents_amount, char c, t_vec2 pos)
{
	game->ents[*ents_amount] = parse_character(game, c, pos);
	if (game->ents[*ents_amount]->type == player)
		game->player = game->ents[*ents_amount];
	if (game->ents[*ents_amount]->type == player || \
		game->ents[*ents_amount]->type == enemy)
		game->ents[++(*ents_amount)] = parse_character(game, '0', pos);
	(*ents_amount)++;
}

int	init_map(t_game *game)
{
	t_vec2	pos;
	int		ents_amount;

	game->ents = malloc(sizeof(t_entity) * MAX_ENTITY_AMOUNT);
	if (!game->ents)
		free_and_exit("alloc for ents", game);
	ents_amount = 0;
	pos.y = -1;
	while (game->map[++pos.y])
	{
		pos.x = -1;
		while (game->map[pos.y][++pos.x])
			process_entity(game, &ents_amount, game->map[pos.y][pos.x], pos);
	}
	game->ents[ents_amount] = NULL;
	return (0);
}
