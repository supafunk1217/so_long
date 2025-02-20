/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcossett <rcossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:13:52 by rcossett          #+#    #+#             */
/*   Updated: 2025/02/13 17:43:09 by rcossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	srand(time(0));
	if (argc != 2)
		return (printf("Error\n Loading failed\n"), 1);
	init_game(&game);
	if (!load_map(&game, argv[1]))
		return (printf("Error\n Error while loading map\n"), 1);
	if (!execute_floodfill(&game))
		return (printf("Error\n No valid path.\n"), 0);
	game.tile_size = 75;
	game.win_size = get_v2(game.tile_size * (game.map_size.x), \
		game.tile_size * (game.map_size.y));
	game.win = mlx_new_window(game.mlx, game.win_size.x, \
		game.win_size.y, "so_long");
	if (!game.win)
		exit(EXIT_FAILURE);
	init_map(&game);
	game.bgr = rescale_xpm(game.mlx, BGR_IMG, game.win_size.x * 2, \
						game.win_size.y * 2);
	init_hooks(&game);
}
