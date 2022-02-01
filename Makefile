NAME = fractol

CC = gcc 
FLAGS = -Wall -Wextra -Werror
SRCS = src/fractol.c src/using.c src/paint.c src/key.c \
		src/paint_mouse.c src/ft_itoa.c
OBJ = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(FLAGS) -Imlx -c $< -o $@

all: $(NAME)
	 
$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx  -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re