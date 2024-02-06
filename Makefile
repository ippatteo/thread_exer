NAME := philo

CC := gcc

CFLAGS := -Wall -Wextra -Werror -g

SOURCE := philosophers/*.c

all:
	$(CC) $(CFLAGS) $(SOURCE) -o $(NAME)

clean: 
	rm -rf $(NAME)

fclean: clean

re: fclean all