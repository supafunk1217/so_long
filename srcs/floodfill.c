/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcossett <rcossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:35:19 by rcossett          #+#    #+#             */
/*   Updated: 2025/02/12 23:54:37 by rcossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	floodfill(char *str, int plr_index, int map_width, int str_len)
{
	if (str[plr_index] == '!' || plr_index < 0 || plr_index > str_len)
		return ;
	if (str[plr_index] == '1')
		return ;
	str[plr_index] = '!';
	floodfill(str, plr_index + 1, map_width, str_len);
	floodfill(str, plr_index - 1, map_width, str_len);
	floodfill(str, plr_index + map_width, map_width, str_len);
	floodfill(str, plr_index - map_width, map_width, str_len);
}

int	get_char_amount(char *str, char to_check)
{
	int	i;
	int	char_amnt;

	char_amnt = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == to_check)
			char_amnt++;
	}
	return (char_amnt);
}

int	get_char_index(char *str, char to_check)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == to_check)
			return (i);
	}
	return (-1);
}

int	execute_floodfill(t_game *game)
{
	char	*full_map;
	char	*old_row;
	int		i;
	int		plr_index;

	i = -1;
	full_map = ft_strdup("");
	while (game->map[++i])
	{
		old_row = ft_strmegajoin(full_map, game->map[i], "\n", NULL);
		free(full_map);
		full_map = old_row;
	}
	plr_index = get_char_index(full_map, 'P');
	floodfill(full_map, plr_index, game->map_size.x + 1, ft_strlen(full_map));
	if (get_char_amount(full_map, 'E') || get_char_amount(full_map, 'C'))
	{
		free(full_map);
		return (0);
	}
	free(full_map);
	return (1);
}
