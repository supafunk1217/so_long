/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcossett <rcossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:36:33 by rcossett          #+#    #+#             */
/*   Updated: 2025/02/13 00:01:20 by rcossett         ###   ########.fr       */
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
	index_xpm = ft_strjoin(index_str, ".xpm");
	full_path = ft_strjoin(path, index_xpm);
	free(index_str);
	free(index_xpm);
	frame = rescale_xpm(game->mlx, full_path, game->tile_size, game->tile_size);
	*size = get_v2(game->tile_size, game->tile_size);
	free(full_path);
	return (frame);
}

void	init_frames(char *path, t_game *game, t_entity *ent, int frames_amount)
{
	void	**frames;
	int		i;

	frames = malloc(sizeof(void *) * (frames_amount + 1));
	if (!frames)
		free_and_exit("Error: malloc failed.", game);
	i = -1;
	while (++i < frames_amount)
		frames[i] = init_frame(game, &ent->size, path, i);
	frames[i] = NULL;
	ent->frames = frames;
	ent->frame_index = 0;
	ent->current_frame = ent->frames[ent->frame_index];
}

char	*ft_strmegajoin(char *a, char *b, char *c, char *d)
{
	char	*a_b;
	char	*a_b_c;
	char	*a_b_c_d;

	if (!a && !b)
		return (NULL);
	if (!b)
		return (a);
	a_b = ft_strjoin(a, b);
	if (!c)
		return (a_b);
	a_b_c = ft_strjoin(a_b, c);
	free(a_b);
	if (!d)
		return (a_b_c);
	a_b_c_d = ft_strjoin(a_b_c, d);
	free(a_b_c);
	return (a_b_c_d);
}

// Construct path > ./includes/sprites/ + "c"
t_entity	*init_entity(t_game *game, char c, t_vec2 pos, t_entity_type type)
{
	t_entity	*new_ent;
	int			frames_amount;
	char		*path;
	char		*str;

	new_ent = malloc(sizeof(t_entity));
	new_ent->pos = get_v2(pos.x * game->tile_size, pos.y * game->tile_size);
	new_ent->start_pos = get_v2(new_ent->pos.x, new_ent->pos.y);
	new_ent->type = type;
	new_ent->active = 1;
	if (type == collectible)
		game->max_collectibles++;
	new_ent->direction = r_range(0, 4);
	frames_amount = 1;
	if (type == player)
		frames_amount = 2;
	else if (type == enemy)
		frames_amount = 3;
	str = ft_strdup(" /");
	str[0] = c;
	path = ft_strjoin(SPRITES_PATH, str);
	init_frames(path, game, new_ent, frames_amount);
	return (free(str), free(path), new_ent);
}
