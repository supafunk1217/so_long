/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcossett <rcossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:00:16 by rcossett          #+#    #+#             */
/*   Updated: 2025/03/12 23:12:02 by rcossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	validate_line(char *line, int width)
{
	int	len;

	if (!line)
		return (0);
	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		len--;
	return (len == width);
}

char	**allocate_map(int height)
{
	char	**map;

	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	return (map);
}

static int	process_line(t_game *game, char *line, int *y_pos)
{
	if (*y_pos == 0)
		game->map_size.x = ft_strlen(line) - 1;
	clean_line(line);
	if (!validate_line(line, game->map_size.x))
		return (0);
	game->map[(*y_pos)++] = ft_strdup(line);
	if (line[0] != '1' || line[ft_strlen(line) - 1] != '1')
		return (0);
	if ((*y_pos == 0 || *y_pos == game->map_size.y) && \
		!only_contains(line, '1'))
		return (0);
	return (1);
}

int	process_map(t_game *game, int fd)
{
	char	*line;
	int		y_pos;
	int		is_valid;

	is_valid = 1;
	line = get_next_line(fd);
	y_pos = 0;
	while (line && y_pos < game->map_size.y)
	{
		if (!process_line(game, line, &y_pos))
			is_valid = 0;
		free(line);
		line = get_next_line(fd);
	}
	game->map[y_pos] = NULL;
	return (is_valid);
}

int	load_map(t_game *game, char *map_path)
{
	int		fd;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (close(fd), free_and_exit("Error\nFile doesn't exist.", game), 0);
	game->map_size.y = count_lines(map_path);
	if (game->map_size.y <= 2)
		free_and_exit("Error\nmap too short", game);
	game->map = allocate_map(game->map_size.y);
	if (!game->map)
		return (0);
	fd = open(map_path, O_RDONLY);
	if (!process_map(game, fd))
		free_and_exit("Error\nNot a RecTanGleeee", game);
	if (game->map_size.x <= 2)
		free_and_exit("Error\nmap too thin", game);
	close(fd);
	return (1);
}
