/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcossett <rcossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:23:03 by rcossett          #+#    #+#             */
/*   Updated: 2025/03/12 22:49:36 by rcossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>	// malloc + free
# include <stdio.h>		// printf pour debug
# include <unistd.h>	// pour write/read
# include <math.h> 		// pour niquer tamere
# include <string.h>	// pour fonctions string
# include <fcntl.h>		// pour open
# include <time.h>

# include "../libraries/libft/includes/libft.h"
# include "../libraries/libft/includes/get_next_line.h"
# include "../libraries/mlx/mlx.h"

# ifdef __APPLE__
#  define KEY_ESC 53
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
# else
#  define KEY_ESC 65307
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_UP 65362
#  define KEY_DOWN 65364
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
# endif

# define MAX_ENTITY_AMOUNT 300
# define ENEMY_SPEED 100000
# define ANIM_REFRESH 10000

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
# define SPRITES_PATH 			"./includes/sprites/"
# define BGR_IMG 				"./includes/sprites/bLxcjh3.xpm"

// vecteur pour la position x * y
typedef struct s_vector2
{
	int	x;
	int	y;
}	t_vec2;

// enum pour la direction potentielle des personnages
typedef enum t_direction
{
	up,
	left,
	right,
	down
}			t_dir;

// types d'entites presentes dans le jeu
typedef enum t_entity_type
{
	wall,
	enemy,
	flooor,
	player,
	collectible,
	exitance
}				t_entity_type;

typedef struct s_entity
{
	void			**frames;
	void			*current_frame;
	int				frame_index;
	t_vec2			size;
	t_vec2			pos;
	t_vec2			start_pos;
	t_dir			direction;
	t_entity_type	type;
	int				active;
}					t_entity;

typedef struct s_game
{
	int			tile_size;
	void		*mlx;
	void		*win;
	void		*bgr;
	char		**map;
	t_entity	**ents;
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

void		init_game(t_game *game);
void		init_hooks(t_game *game);
int			init_map(t_game *game);

int			load_map(t_game *game, char *map_path);
int			count_lines(char *map_path);
char		**allocate_map(int height);
void		clean_line(char *line);
int			execute_floodfill(t_game *game);

t_entity	*init_entity(t_game *game, char c, t_vec2 pos, t_entity_type type);
t_entity	*parse_character(t_game *game, char c, t_vec2 pos);
int			update_enemy(t_game *game, t_entity *ent, int index);

int			is_move_valid(t_game *game, t_vec2 new_pos);
t_entity	*get_ent_at_position(t_game *game, t_vec2 pos, t_entity *me);
void		handle_move(t_game *game, int direction);

void		render_game(t_game *game);
void		*rescale_xpm(void *mlx, char *path, int new_w, int new_h);

int			handle_keypress(int keycode, t_game *game);
int			handle_close(t_game *game);
int			update(t_game *game);

t_vec2		get_v2(int x, int y);
int			cmp_vec2(t_vec2 a, t_vec2 b);
int			get_urandom(int min, int max);
int			r_range(int min, int max);
char		*ft_strmegajoin(char *a, char *b, char *c, char *d);
void		free_and_exit(char *exit_msg, t_game *game);
int			char_counter(char *str, char c);
int			only_contains(char *line, char c);

#endif