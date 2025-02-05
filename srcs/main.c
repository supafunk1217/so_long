/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcossett <rcossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:13:52 by rcossett          #+#    #+#             */
/*   Updated: 2025/01/23 02:19:41 by rcossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	srand(time(0));
	if (argc != 2)
	{
		printf("Error loading so_long :(\n");
		return (1);
	}
	init_game(&game);
	if (!load_map(&game, argv[1]))
	{
		printf("Error loading map... Oops\n");
		return (1);
	}
	game.win_size = get_v2(TILE_SIZE * (game.map_size.x * WIN_W_RATIO), \
		TILE_SIZE * (game.map_size.y * WIN_H_RATIO));
	game.win = mlx_new_window(game.mlx, game.win_size.x, \
		game.win_size.y, "so_long");
	if (!game.win)
		exit(EXIT_FAILURE);
	init_map(&game);
	init_hooks(&game);
}
