/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcossett <rcossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:28:37 by rcossett          #+#    #+#             */
/*   Updated: 2025/02/12 19:36:09 by rcossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	check_counts(int p_count, int e_count, int c_count)
{
	if (p_count != 1)
		return (0);
	if (e_count != 1)
		return (0);
	if (c_count < 1)
		return (0);
	return (1);
}

static int	count_elements(t_game *game)
{
	int		p_count;
	int		e_count;
	int		c_count;
	int		i;
	int		j;

	p_count = 0;
	e_count = 0;
	c_count = 0;
	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == 'P')
				p_count++;
			else if (game->map[i][j] == 'E')
				e_count++;
			else if (game->map[i][j] == 'C')
				c_count++;
		}
	}
	return (check_counts(p_count, e_count, c_count));
}

static int	is_map_valid(t_game *game)
{
	int		i;

	i = 0;
	while (game->map[i])
	{
		if ((int)ft_strlen(game->map[i]) != game->map_size.x)
			return (0);
		i++;
	}	
	return (1);
}

int	validate_parsed_map(t_game *game)
{
	if (!is_map_valid(game))
		return (0);
	if (!count_elements(game))
		return (0);
	return (1);
}
