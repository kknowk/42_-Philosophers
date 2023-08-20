NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
# CFLAGS += -g -fsanitize=address
# CFLAGS += -g -fsanitize=thread

SRCS = main_bonus.c \
	fork_management_bonus.c \
	philo_init_bonus.c \
	philo_routine_bonus.c \
	time_management_bonus.c \
	utils_bonus.c \
	utils_err_bonus.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
