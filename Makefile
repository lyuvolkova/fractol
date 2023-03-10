NAME = fractol

CC = gcc 
FLAGS = -Wall -Wextra -Werror
SRCS = fractol.c using.c paint.c key.c paint_mouse.c
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