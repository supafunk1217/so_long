/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcossett <rcossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:36:15 by rcossett          #+#    #+#             */
/*   Updated: 2025/01/22 17:39:30 by rcossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

char	**allocate_map(int height)
{
	char	**map;

	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	return (map);
}

void	clean_line(char *line)
{
	if (line && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
}

t_vec2	get_v2(int x, int y)
{
	t_vec2 vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}

//		returns a random value betwewen min and max
int r_range(int min, int max)
{
    if (min > max)
        return -1;
    return (rand() % (max - min + 1) + min);
}