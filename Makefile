NAME 		= 	so_long
LIBFT 		= 	./libraries/libft/libft.a
MLX_DIR 	= 	./libraries/mlx
LIBRARY 	= 	-L$(MLX_DIR) -lmlx -lX11 -lXext -lm

GAME_MAIN	= srcs/main.c

SRCS 		= 	srcs/map_utils.c \
				srcs/map_utils2.c \
				srcs/render.c \
				srcs/hooks.c \
				srcs/init.c \
				srcs/map_parser.c \
				srcs/update.c \
				srcs/init_map.c \
				srcs/close.c \
				srcs/collisions.c

OBJS 		= 	$(SRCS:.c=.o)
GAME_OBJ	= $(GAME_MAIN:.c=.o)
CC 			= 	gcc	
#CFLAGS 	= 	-Wall -Werror -Wextra -I./includes -I$(MLX_DIR)
CFLAGS 		= 	-Wall -Wextra -I./includes -I$(MLX_DIR)

RM 			= 	rm -rf
AR 			= 	ar rcs

RMAP_SRC	=	srcs/map_gen.c
RMAP_OBJ	=	$(RMAP_SRC:.c=.o)
RMAP_NAME	=	rmap

all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "Building libft... Plese wait."
	@make -C ./libraries/libft > /dev/null 2>&1

$(NAME): ${OBJS} $(GAME_MAIN) ${LIBFT}
	@echo "Building so_long... Please wait."
	@${CC} ${OBJS} $(GAME_MAIN) ${LIBFT} $(LIBRARY) -o ${NAME}

$(RMAP_NAME): ${OBJS} $(RMAP_OBJ) $(LIBFT)
	@echo "Building map generator... Please wait."
	@${CC} ${OBJS} $(RMAP_OBJ) $(LIBFT) $(LIBRARY) -o $(RMAP_NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning..."
	@rm -f $(OBJS)
	@make clean -C ./libraries/libft > /dev/null 2>&1
	@echo "Done !"

fclean: clean
	@echo "Cleaning all..."
	@rm -f $(NAME)
	@make fclean -C ./libraries/libft > /dev/null 2>&1
	@echo "Done !"

re: fclean all

.PHONY: all clean fclean re