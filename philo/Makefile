NAME = philo

SRCS = srcs/philo.c \
	srcs/parsing.c \
	srcs/utils.c

INCS = incs/philo.h

CC = gcc

CFLAGS = -Wall -Werror -Wextra -pthread -fsanitize=thread

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
_WHITE = $'\033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(_CYAN)compiling project Philosophers$(_WHITE)"
	$(CC) $(CFLAGS) -o $@ $(OBJS)
	@echo "$(_GREEN)Philosophers project compiled$(_WHITE)"

%.o : %.clean
	$(CC) $(CFLAGS) -I $(INCS) -o ${<:.c=.o} -c $<

clean:
	@echo "$(_YELLOW)Deleting object files$(_WHITE)"
	rm -rf $(OBJS)
	@echo "$(_GREEN)Deleted object files$(_WHITE)"

fclean: clean
	@echo "$(_YELLOW)Deleting binary$(_WHITE)"
	rm -rf $(NAME)
	@echo "$(_GREEN)Deleted binary$(_WHITE)"

re : fclean all

.PHONY: all clean fclean re