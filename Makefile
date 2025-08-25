CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = philo
SRC_FILES = philo.c philo_utils.c set_rules.c\
			free_stuff.c philo_cycle.c\
			create_philos_and_forks.c struct_utils.c\
			routine_utils.c\

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
