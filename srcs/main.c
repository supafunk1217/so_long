/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcossett <rcossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:13:52 by rcossett          #+#    #+#             */
/*   Updated: 2025/03/12 23:01:44 by rcossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	set_window_size(t_game *game)
{
	game->tile_size = 75;
	if (game->map_size.x > 30 || game->map_size.y > 30)
	{
		game->tile_size = 1950 / game->map_size.y;
		if (game->map_size.x > game->map_size.y)
			game->tile_size = 1950 / game->map_size.x;
	}
	game->win_size = get_v2(game->tile_size * (game->map_size.x), \
		game->tile_size * (game->map_size.y));
	game->win = mlx_new_window(game->mlx, game->win_size.x, \
		game->win_size.y, "so_long");
	if (!game->win)
		exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_game	game;
	char	*file_extension;

	if (argc != 2)
		return (printf("Error\nLoading failed\n"), 1);
	file_extension = ft_strchr(argv[1], '.');
	if (!file_extension || ft_strncmp(file_extension, ".ber", 5))
		return (printf("wrong file extension\n"), 0);
	init_game(&game);
	if (!load_map(&game, argv[1]))
		return (printf("Error\nError while loading map\n"), 1);
	if (!execute_floodfill(&game))
		return (printf("Error\nNo valid path.\n"), 0);
	set_window_size(&game);
	init_map(&game);
	if (game.bgr)
	{
		mlx_destroy_image(game.mlx, game.bgr);
		game.bgr = NULL;
	}
	game.bgr = rescale_xpm(game.mlx, BGR_IMG, game.win_size.x, \
						game.win_size.y);
	init_hooks(&game);
}
