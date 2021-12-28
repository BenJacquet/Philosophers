NAME = philo

SRCS = srcs/philo.c

INCS = incs/philo.h

CC = gcc

CFLAGS = -Wall -Werror -Wextra -pthread

OBJS = $(SRCS:.c=.o)

# Colors
_BLACK = $'\033[30m
_RED = $'\033[31m
_GREEN = $'\033[32m
_YELLOW = $'\033[33m
_BLUE = $'\033[34m
_PURPLE = $'\033[35m
_CYAN = $'\033[36m
_GREY = $'\033[37m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(_CYAN)compiling project Philosophers"
	$(CC) $(CFLAGS) -o $@ $(OBJS)
	@echo "$(_GREEN)Philosophers project compiled"

%.o : %.clean
	@echo "$(_CYAN)Generating object files"
	$(CC) $(CFLAGS) -I $(INCS) -o ${<:.c=.o} -c $<
	@echo "$(_GREEN)Object files are ready"

clean:
	echo "$(_YELLOW)Deleting object files"
	rm -f $(OBS)
	echo "$(_GREEN)Deleted object files"

fclean: clean
	echo "$(_YELLOW)Deleting binary"
	rm -f $(NAME)
	echo "$(_GREEN)Deleted binary"

re : fclean all

.PHONY: all clean fclean re