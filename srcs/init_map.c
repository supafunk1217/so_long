/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcossett <rcossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:14:08 by rcossett          #+#    #+#             */
/*   Updated: 2025/01/22 23:35:29 by rcossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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
	frame = mlx_xpm_file_to_image(game->mlx, full_path, &size->x, &size->y);
	free(full_path);
	return (frame);
}
void	init_frames(char *path, t_game *game, t_entity *ent, int frames_amount)
{
	void	**frames;
	int		i;

	frames = malloc(sizeof(void *) * frames_amount);
	if (!frames)
		exit(0);
	i = -1;
	while (++i < frames_amount)
		frames[i] = init_frame(game, &ent->size, path, i);
	frames[i] = NULL;
	ent->frames = frames;
	ent->frame_index = 0;
	ent->current_frame = ent->frames[ent->frame_index];
}

// Construct path > ./includes/sprites/ + "c"
t_entity	*init_entity(t_game *game, char c, t_vec2 pos, t_entity_type type)
{
	t_entity	*new_ent;
	int			frames_amount;
	char		*path;
	char		*str;

	str = malloc(3);
	if (!str)
		exit(0);
	str[0] = c;
	str[1] = '/';
	str[2] = '\0';
	new_ent = malloc(sizeof(t_entity));
	new_ent->pos = get_v2(pos.x * TILE_SIZE, pos.y * TILE_SIZE);
	new_ent->start_pos = get_v2(new_ent->pos.x, new_ent->pos.y);
	new_ent->type = type;
	new_ent->state = idle;
	new_ent->active = 1;
	if (type == collectible)
		game->max_collectibles++;
	new_ent->direction = r_range(0, 4);
	path = ft_strjoin(SPRITES_PATH, str);
	free(str);
	frames_amount = 1;
	if (type == player)
		frames_amount = 2;
	else if (type == enemy)
		frames_amount = 3;
	init_frames(path, game, new_ent, frames_amount);
	printf("[x%dy%d %c]", new_ent->pos.x / TILE_SIZE, new_ent->pos.y / TILE_SIZE, c);
	return (new_ent);
}

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

int	init_map(t_game *game)
{
	t_vec2	pos;
	int		entities_amount;

	game->entities = malloc(sizeof(t_entity) * MAX_ENTITY_AMOUNT);
	if (!game->entities)
		exit(0);
	entities_amount = 0;
	pos.y = 0;
	while (game->map[pos.y])
	{
		pos.x = 0;
		while (game->map[pos.y][pos.x])
		{	
			game->entities[entities_amount] = parse_character(game, game->map[pos.y][pos.x], pos);
			if (game->entities[entities_amount]->type == player)
				game->player = game->entities[entities_amount];
			if (game->entities[entities_amount]->type == player || game->entities[entities_amount]->type == enemy)
				game->entities[++entities_amount] = parse_character(game, '0', pos);
			entities_amount++;
			pos.x++;
		}
		printf("\n");
		pos.y++;
	}
	game->entities[entities_amount] = NULL;
	printf("%d\n", game->max_collectibles);
	return (0);
}
