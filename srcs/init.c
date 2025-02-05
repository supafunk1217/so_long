/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcossett <rcossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:47:43 by rcossett          #+#    #+#             */
/*   Updated: 2025/01/23 02:18:36 by rcossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit(EXIT_FAILURE);
	game->win = NULL;
	game->map_size = get_v2(0, 0);
	game->moves = 0;
	game->collectibles = 0;
	game->max_collectibles = 0;
	game->initialized = 0;
	game->time = 0;
	game->bgr = mlx_xpm_file_to_image(game->mlx, BGR_IMG, &game->bgr_size.x, &game->bgr_size.y);
}
