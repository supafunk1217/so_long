/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcossett <rcossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:23:03 by rcossett          #+#    #+#             */
/*   Updated: 2025/02/05 18:39:11 by rcossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h> // malloc + free
# include <stdio.h> // printf pour debug
# include <unistd.h> // pour write/read
# include <math.h> // pour niquer tamere
# include <string.h> // pour fonctions string
# include <fcntl.h> // pour open
# include <time.h>

# include "../libraries/libft/includes/libft.h"
# include "../libraries/libft/includes/get_next_line.h"
# include "../libraries/mlx/mlx.h"

# ifdef __APPLE__
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# else
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# endif

# define WIN_W_RATIO 1
# define WIN_H_RATIO 1

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_MOUSE_PRESS 4
# define X_EVENT_MOUSE_RELEASE 5
# define X_EVENT_EXIT 17

# define WALL			'1'
# define FLOOR 			'0'
# define PLAYER			'P'
# define ENEMY			'F'
# define COLLECTIBLE	'C'
# define EXIT 			'E'

# define TILE_SIZE 32

# define SPRITES_PATH 			"./includes/sprites/"

# define ANIM_REFRESH 10000

# define ENEMY_SPEED 100000

# define MAX_ENTITY_AMOUNT 300

# define BGR_IMG "./includes/sprites/BGR_JUNGLE.xpm"

typedef struct s_vector2 // vecteur pour la position x * y
{
	int x;
	int y;
}	t_vec2;

typedef enum	e_direction // enum pour la direction potentielle des personnages
{
	up,
	left,
	right,
	down
}	e_dir;

typedef enum	e_entity_type // types d'entites presentes dans le jeu
{
	wall,
	enemy,
	flooor,
	player,
	collectible,
	exitance
}				t_entity_type;

typedef enum	e_entity_state
{
	idle,
	walk,
	attack,
}				t_entity_state;

typedef struct	s_entity
{
	void			**frames;
	void			*current_frame;
	int				frame_index;
	t_vec2			size;
	t_vec2			pos;
	t_vec2			start_pos;
	e_dir			direction;
	t_entity_type	type;
	t_entity_state	state;
	int				active; // it tells us if the entity is active (should be rendered and updated)
}					t_entity;

/* structure du jeu */
typedef struct		s_game
{
	void		*mlx; // mlx
	void		*win; // fenetre
	void		*bgr; // background
	char		**map; // array pour map
	t_entity	**entities;
	t_entity	*player;
	t_vec2		map_size;
	int			moves;
	int			collectibles;
	int			max_collectibles;
	int			initialized;
	int			time;
	t_vec2		win_size;
	t_vec2		bgr_size;
	double		time_at_start;
}					t_game;

/* fonctions presentes et prototypes */

//			PARSING
int			count_lines(char *map_path);
char		**allocate_map(int height);
void		clean_line(char *line);

//			HOOKS
int			handle_keypress(int keycode, t_game *game);
int			handle_close(t_game *game);

//			INIT
void		init_hooks(t_game *game);
int			load_map(t_game *game, char *map_path);
void		init_game(t_game *game);
int			init_map(t_game *game);

//			UPDATE
int			update(t_game *game);

//			render
void		render_game(t_game *game);

//			UTILS
t_vec2		get_v2(int x, int y);
int			cmp_vec2(t_vec2 a, t_vec2 b);

int 		r_range(int min, int max);
int			is_move_valid(t_game *game, t_vec2 new_pos);
t_entity	*get_ent_at_position(t_game *game, t_vec2 pos, t_entity *me);
void		free_and_exit(t_game *game);

#endif