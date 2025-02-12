/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcossett <rcossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:00:16 by rcossett          #+#    #+#             */
/*   Updated: 2025/02/12 23:14:11 by rcossett         ###   ########.fr       */
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

static int	process_line(t_game *game, char *line, int *i)
{
	if (*i == 0)
		game->map_size.x = ft_strlen(line) - 1;
	clean_line(line);
	if (!validate_line(line, game->map_size.x))
		return (0);
	game->map[(*i)++] = ft_strdup(line);
	return (1);
}

void	process_map(t_game *game, int fd)
{
	char	*line;
	int		i;

	line = get_next_line(fd);
	i = 0;
	while (line && i < game->map_size.y)
	{
		if (!process_line(game, line, &i))
		{
			while (i > 0)
				free(game->map[--i]);
			free(line);
			return ;
		}
		free(line);
		line = get_next_line(fd);
	}
	game->map[i] = NULL;
}

int	load_map(t_game *game, char *map_path)
{
	int		fd;

	game->map_size.y = count_lines(map_path);
	if (game->map_size.y <= 0)
		return (0);
	game->map = allocate_map(game->map_size.y);
	if (!game->map)
		return (0);
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (printf("Error while opening map.\n"), 0);
	process_map(game, fd);
	close(fd);
	return (1);
}
