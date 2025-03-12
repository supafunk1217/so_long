/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcossett <rcossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:31:04 by rcossett          #+#    #+#             */
/*   Updated: 2025/02/27 13:39:38 by rcossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	handle_move(t_game *game, int direction)
{
	t_vec2	new_pos;

	new_pos = game->player->pos;
	if (direction == up)
		new_pos.y -= game->tile_size;
	else if (direction == down)
		new_pos.y += game->tile_size;
	else if (direction == left)
		new_pos.x -= game->tile_size;
	else if (direction == right)
		new_pos.x += game->tile_size;
	if (is_move_valid(game, new_pos))
	{
		game->player->pos = new_pos;
		game->player->direction = direction;
		if (direction == right)
			game->player->current_frame = game->player->frames[1];
		if (direction == left)
			game->player->current_frame = game->player->frames[0];
		game->moves++;
		printf("Moves: %i\n", game->moves);
	}
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		free_and_exit(NULL, game);
	if (keycode == KEY_W || keycode == KEY_UP)
		handle_move(game, up);
	if (keycode == KEY_A || keycode == KEY_LEFT)
		handle_move(game, left);
	if (keycode == KEY_S || keycode == KEY_DOWN)
		handle_move(game, down);
	if (keycode == KEY_D || keycode == KEY_RIGHT)
		handle_move(game, right);
	return (0);
}

int	handle_close(t_game *game)
{
	free_and_exit(NULL, game);
	exit (0);
}
