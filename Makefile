NAME := philo

CC := gcc

CFLAGS := -Wall -Wextra -Werror -g

SOURCE := Philo/*.c

all:
	make -C $(LIBFT)
	$(CC) $(CFLAGS) $(SOURCE) -o $(NAME)

clean: fclean

fclean: clean
		make clean -C $(LIBFT)
		rm -rf $(NAME)

re: fclean all