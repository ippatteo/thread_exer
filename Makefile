NAME := philo

CC := gcc

CFLAGS := -Wall -Wextra -Werror -g

SOURCE := philosophers/*.c

all:
	$(CC) $(CFLAGS) $(SOURCE) -o $(NAME)

clean: fclean

fclean: clean
		make clean -C $(LIBFT)
		rm -rf $(NAME)

re: fclean all