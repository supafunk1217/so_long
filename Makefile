NAME	=	so_long
LIBFT	=	./libraries/libft/libft.a
MLX_DIR =	./libraries/mlx
LIBRARY =	-L$(MLX_DIR) -lmlx -lX11 -lXext -lm

UTILS_SRCS =	\
srcs/map_utils.c \
srcs/render.c \
srcs/hooks.c \
srcs/map_parser.c \
srcs/collisions.c \
srcs/game_utils.c \
srcs/map_validator.c \
srcs/enemy_move.c \
srcs/init_game.c \
srcs/game_exit.c \
srcs/entity_init.c \
srcs/entity_update.c \
srcs/rescale_xpm.c \
srcs/floodfill.c

SO_LONG_SRC = srcs/main.c
RMAP_SRC = srcs/map_gen.c

UTILS_OBJ = $(UTILS_SRCS:.c=.o)
SO_LONG_OBJ = $(SO_LONG_SRC:.c=.o)
RMAP_OBJ = $(RMAP_SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -I./includes -I$(MLX_DIR)
RM = rm -rf

all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "Building libft... Please wait."
	@make -C ./libraries/libft > /dev/null 2>&1

$(NAME): $(UTILS_OBJ) $(SO_LONG_OBJ) $(LIBFT)
	@echo "Building so_long... Please wait."
	@$(CC) $(UTILS_OBJ) $(SO_LONG_OBJ) $(LIBFT) $(LIBRARY) -o $(NAME)
	@echo "✅ Done!"

rmap: $(UTILS_OBJ) $(RMAP_OBJ) $(LIBFT)
	$(CC) $(UTILS_SRCS) $(RMAP_SRC) $(LIBFT) $(LIBRARY) -o rmap

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

debug: $(UTILS_OBJ) $(SO_LONG_OBJ) $(LIBFT)
	@$(CC) -fsanitize=address $(UTILS_OBJ) $(SO_LONG_OBJ) $(LIBFT) $(LIBRARY) -o $(NAME)

clean:
	@echo "🧹 Cleaning..."
	@$(RM) $(SO_LONG_OBJ)
	@make clean -C ./libraries/libft > /dev/null 2>&1
	@echo "✨ Clean complete!"

fclean: clean
	@echo "🧹 Cleaning all..."
	@$(RM) $(NAME)
	@$(RM) $(RMAP_OBJ)
	@$(RM) $(UTILS_OBJ)
	@$(RM) $(SO_LONG_OBJ)
	@make fclean -C ./libraries/libft > /dev/null 2>&1
	@echo "✨ Full clean complete!"

re: fclean all

.PHONY: all clean fclean re