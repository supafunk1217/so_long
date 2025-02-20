/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcossett <rcossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:36:33 by rcossett          #+#    #+#             */
/*   Updated: 2025/02/13 18:13:56 by rcossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

t_entity	*parse_character(t_game *game, char c, t_vec2 pos)
{
	if (c == 'P')
		return (init_entity(game, c, pos, player));
	else if (c == '1')
		return (init_entity(game, c, pos, wall));
	else if (c == '0')
		return (init_entity(game, c, pos, flooor));
	else if (c == 'C')
		return (init_entity(game, c, pos, collectible));
	else if (c == 'E')
		return (init_entity(game, c, pos, exitance));
	else if (c == 'F')
		return (init_entity(game, c, pos, enemy));
	else
		return (NULL);
}

void	*init_frame(t_game *game, t_vec2 *size, char *path, int index)
{
	char	*full_path;
	char	*index_str;
	char	*index_xpm;
	void	*frame;

	index_str = ft_itoa(index);
	if (!index_str)
		return (NULL);
	index_xpm = ft_strjoin(index_str, ".xpm");
	free(index_str);
	if (!index_str)
		return (NULL);
	full_path = ft_strjoin(path, index_xpm);
	free(index_xpm);
	if (!full_path)
		return (NULL);
	frame = rescale_xpm(game->mlx, full_path, game->tile_size, game->tile_size);
	free(full_path);
	if (!frame)
		return (NULL);
	*size = get_v2(game->tile_size, game->tile_size);
	return (frame);
}

void	init_frames(char *path, t_game *game, t_entity *ent, int frames_amount)
{
	void	**frames;
	int		i;

	frames = malloc(sizeof(void *) * (frames_amount + 1));
	if (!frames)
		free_and_exit("Error\n Malloc failed\n", game);
	i = -1;
	while (++i < frames_amount)
	{
		frames[i] = init_frame(game, &ent->size, path, i);
		if (!frames[i])
		{
			while (--i >= 0)
				mlx_destroy_image(game->mlx, frames[i]);
			free(frames);
			free_and_exit("Error\n Frame initialization failed\n", game);
		}
	}
	frames[i] = NULL;
	ent->frames = frames;
	ent->frame_index = 0;
	ent->current_frame = ent->frames[ent->frame_index];
}

static int	ent_prop(t_entity *ent, t_game *game, t_entity_type type)
{
	int	frames_amount;

	ent->active = 1;
	ent->type = type;
	ent->direction = r_range(0, 4);
	if (type == collectible)
		game->max_collectibles++;
	frames_amount = 1;
	if (type == player)
		frames_amount = 2;
	else if (type == enemy)
		frames_amount = 3;
	return (frames_amount);
}

// Construct path > ./includes/sprites/ + "c"
t_entity	*init_entity(t_game *game, char c, t_vec2 pos, t_entity_type type)
{
	t_entity	*new_ent;
	char		*path;
	char		*str;

	new_ent = malloc(sizeof(t_entity));
	if (!new_ent)
		free_and_exit("Error\n Malloc failed\n", game);
	new_ent->pos = get_v2(pos.x * game->tile_size, pos.y * game->tile_size);
	new_ent->start_pos = get_v2(new_ent->pos.x, new_ent->pos.y);
	str = ft_strdup(" /");
	if (!str)
	{
		free(new_ent);
		free_and_exit("Error\n strdup failed\n", game);
	}
	str[0] = c;
	path = ft_strjoin(SPRITES_PATH, str);
	if (!path)
	{
		free(str);
		free(new_ent);
		free_and_exit("Error\n strjoin failed\n", game);
	}
	init_frames(path, game, new_ent, ent_prop(new_ent, game, type));
	return (free(str), free(path), new_ent);
}
