NAME		=	so_long
LIBFT		=	./libraries/libft/libft.a
MLX_DIR 	=	./libraries/mlx
LIBRARY 	=	-L$(MLX_DIR) -lmlx -lX11 -lXext -lm

UTILS_SRCS	=	\
				srcs/map_utils.c \
				srcs/render.c \
				srcs/hooks.c \
				srcs/map_parser.c \
				srcs/collisions.c \
				srcs/game_utils.c \
				srcs/enemy_move.c \
				srcs/init_game.c \
				srcs/game_exit.c \
				srcs/entity_init.c \
				srcs/entity_update.c \
				srcs/rescale_xpm.c \
				srcs/floodfill.c

SO_LONG_SRC	= srcs/main.c
RMAP_SRC	= srcs/map_gen.c

SO_LONG_OBJ = $(SO_LONG_SRC:.c=.o)
UTILS_OBJ	= $(UTILS_SRCS:.c=.o)
RMAP_OBJ	= $(RMAP_SRC:.c=.o)

CC			= gcc
CFLAGS		= -Wall -Wextra -g -I./includes -I$(MLX_DIR)
RM			= rm -rf

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C ./libraries/libft

$(NAME): $(UTILS_OBJ) $(SO_LONG_OBJ) $(LIBFT)
	$(CC) $(UTILS_OBJ) $(SO_LONG_OBJ) $(LIBFT) $(LIBRARY) -o $(NAME)

rmap: $(UTILS_OBJ) $(RMAP_OBJ) $(LIBFT)
	$(CC) $(UTILS_SRCS) $(RMAP_SRC) $(LIBFT) $(LIBRARY) -o rmap

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

debug: $(UTILS_OBJ) $(SO_LONG_OBJ) $(LIBFT)
	$(CC) -fsanitize=address $(UTILS_OBJ) $(SO_LONG_OBJ) $(LIBFT) $(LIBRARY) -o $(NAME)

clean:
	$(RM) $(SO_LONG_OBJ) $(UTILS_OBJ)
	make clean -C ./libraries/libft

fclean: clean
	$(RM) $(NAME)
	$(RM) $(RMAP_OBJ)
	$(RM) $(UTILS_OBJ)
	$(RM) $(SO_LONG_OBJ)
	make fclean -C ./libraries/libft

re: fclean all

.PHONY: all clean fclean re
