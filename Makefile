CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = philo
SRC_FILES = philo.c
OBJ_FILES = $(SRC_FILES:.c=.o)


$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: clean
.SECONDARY: $(OBJ_FILES)
