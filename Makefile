NAME	= 	so_long

LIBFT	=	./includes/libft/libft.a

MLX_DIR	=	./libraries/minilibx-linux

LIBRARY	=	-L$(MLX_DIR) -lmlx -lx11 -lXext -lm

SRCS	= 	xxx.c \
			blabla.x

OBJS	=	$(SRCS.c=.o)

CC		= 	gcc

CFLAGS	= 	-Wall -Werror -Wextra

RM		=	rm -rf

AR		= 	ar rcs

all:		$(LIBFT) $(NAME)

$(NAME):	$(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) $(FLAGS) $(LIBRARY) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean:		clean
	@rm -f $(NAME)

re			fclean all

.PHONY:		all clean fclean re