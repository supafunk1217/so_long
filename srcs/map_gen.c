/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_gen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcossett <rcossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 01:28:28 by rcossett          #+#    #+#             */
/*   Updated: 2025/03/12 21:09:06 by rcossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

char	*get_map(t_vec2 size)
{
	char	*map_content;
	int		i;
	t_vec2	pos;

	map_content = malloc((size.x + 1) * size.y + 1);
	pos = get_v2(0, 0);
	i = 0;
	while (pos.y < size.y)
	{
		pos.x = 0;
		while (pos.x < size.x)
		{
			if (pos.x == 0 || pos.x == size.x - 1 || \
				pos.y == 0 || pos.y == size.y - 1)
				map_content[i++] = '1';
			else
				map_content[i++] = '0';
			pos.x++;
		}
		if (pos.y != size.y - 1)
			map_content[i++] = '\n';
		pos.y++;
	}
	map_content[i] = '\0';
	return (map_content);
}

void	add_character(char *map, char c, int len)
{
	int	random_index;

	random_index = r_range(0, len);
	while (map[random_index] != '0')
		random_index = r_range(0, len);
	map[random_index] = c;
}

void	populate_with_ents(char *map)
{
	int	len;
	int	wall_ratio;
	int	ennemy_ratio;
	int	coll_ratio;
	int	i;

	len = ft_strlen(map);
	add_character(map, 'P', len);
	add_character(map, 'E', len);
	wall_ratio = 10;
	ennemy_ratio = 50;
	coll_ratio = 5;
	i = 0;
	while (i++ < len / wall_ratio)
		add_character(map, '1', len);
	i = 0;
	while (i++ < len / coll_ratio)
		add_character(map, 'C', len);
	i = 0;
	while (i++ < len / ennemy_ratio)
		add_character(map, 'F', len);
}

void	add_to_file(char *file_name, char *content)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0641);
	write(fd, content, ft_strlen(content));
}

int	main(int argc, char *argv[])
{
	char	*map_name;
	char	*map_content;
	t_vec2	map_size;

	map_name = ft_strdup("Randomap.ber");
	map_size = get_v2(15, 8);
	if (argc >= 2)
		map_size.x = ft_atoi(argv[1]);
	if (argc >= 3)
	{
		map_size.y = ft_atoi(argv[2]);
		if (map_size.y >= map_size.x)
			map_size.y = map_size.x -1;
	}
	map_content = get_map(map_size);
	populate_with_ents(map_content);
	add_to_file(map_name, map_content);
}
