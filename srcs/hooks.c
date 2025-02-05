/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcossett <rcossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:31:04 by rcossett          #+#    #+#             */
/*   Updated: 2025/01/23 02:18:00 by rcossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		free_and_exit(game);
	if (keycode == KEY_W && is_move_valid(game, get_v2(game->player->pos.x, game->player->pos.y - TILE_SIZE)))
	{
		game->player->pos.y -= TILE_SIZE;
		game->player->direction = up;
	}
	else if (keycode == KEY_A && is_move_valid(game, get_v2(game->player->pos.x - TILE_SIZE, game->player->pos.y)))
	{
		game->player->pos.x -= TILE_SIZE;
		game->player->direction = left;
		game->player->current_frame = game->player->frames[0];
	}
	else if (keycode == KEY_S && is_move_valid(game, get_v2(game->player->pos.x, game->player->pos.y + TILE_SIZE)))
	{
		game->player->pos.y += TILE_SIZE;
		game->player->direction = down;
	}
	else if (keycode == KEY_D && is_move_valid(game, get_v2(game->player->pos.x + TILE_SIZE, game->player->pos.y)))
	{
		game->player->pos.x += TILE_SIZE;
		game->player->direction = right;
		game->player->current_frame = game->player->frames[1];
	}
	return (0);
}

int	handle_close(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
}

void	init_hooks(t_game *game)
{
	mlx_loop_hook(game->mlx, update, (void *)game);
	mlx_key_hook(game->win, handle_keypress, game);
	mlx_loop(game->mlx);
	//mlx_hook(game->win, X_EVENT_KEY_PRESS, 0, &handle_keypress, game);
	//mlx_hook(game->win, X_EVENT_EXIT, 0, &handle_keypress, game);
}
