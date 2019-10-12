#ifndef SOCKET.H
#define SOCKET.H

SRC = server.c client.c
NAME1 = server
NAME2 = client
FLAGS = -Wall -Wextra -Werror -g -ggdb3
OBJ = $(SRC:.c=.o)

all: $(NAME1) $(NAME2)
$(NAME1):
	# make -C libft/
	@gcc $(FLAGS) server.c -o $(NAME1)

$(NAME2):
	@gcc $(FLAGS) client.c -o $(NAME2)

clean	:
	# make -C libft/
	rm -f $(OBJ)

fclean	: clean
	# make -C libft/
	rm -rf $(NAME1) $(NAME2)

re		: fclean all