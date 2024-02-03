NAME	= tetris
SRCS	= tetris.c
OBJS	= $(SRCS:.c=.o)
FLAG	= -lncurses
CC		= gcc
RM		= rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(FLAG) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re