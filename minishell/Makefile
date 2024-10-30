SRCS = $(wildcard *.c) #ADD ACTUAL SOURCES!!!
#SRCS = main.c signals.c start_program.c tokenize.c utils.c utils_token.c


OBJS = $(SRCS:.c=.o)

NAME = minishell

CC = cc
RM = rm -f

CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
