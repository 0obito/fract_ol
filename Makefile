CC = cc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -lmlx -lXext -lX11
NAME = fractol
SRC = fractol.c init_program.c generate_fractal.c parsing.c ft_atod.c hook_functions.c
OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLXFLAGS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: clean

.SECONDARY: $(OBJ)
