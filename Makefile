#ifndef SOCKET.H
#define SOCKET.H

SRC = server.c client.c
NAME1 = server
NAME2 = client
FLAGS = -Wall -Wextra -Werror
OBJ = $(SRC:.c=.o)

all: $(NAME1) $(NAME2)
.PHONY: all
$(NAME1):
	# make -C libft/
	@gcc -c $(FLAGS) $(SRC)
	ar rc $(NAME1) $(OBJ)
	ranlib $(NAME1)
$(NAME2):
	# @gcc -c $(FLAGS) $(SRC)
	ar rc $(NAME2) $(OBJ)
	ranlib $(NAME2)
clean	:
	# make -C libft/
	rm -f $(OBJ)

fclean	: clean
	# make -C libft/
	rm -rf $(NAME1) $(NAME2)

re		: fclean all