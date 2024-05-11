NAME = pipex
FLAGS = -Wall -Werror -Wextra
CC = cc
SRC = error.c utils.c parsing.c
OBJ = $(SRC:.c=.o)
LIBFT = $(LIBFTDIR)/libft.a
LIBFTDIR = ./libft

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFTDIR) fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re