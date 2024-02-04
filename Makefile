NAME	= tetris
SRC_DIR	= ./srcs
SRC		= tetris.c \
			finish/finish.c \
			init/init.c \
			operation/handle_blocks.c \
			operation/move.c \
			operation/rotate.c \
			utils/create_shape.c \
			utils/delete_shape.c \
			utils/generate_block.c \
			utils/is_movable.c \
			utils/is_update.c \
			utils/print_shape.c \
			utils/rotate_shape.c \
			utils/structs_array.c

SRCS	=	$(addprefix $(SRC_DIR)/, $(SRC))
OBJ_DIR =	./objs
OBJS	=	$(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))
CC		=	cc
CFLAGS	=	-Wall -Wextra -MMD -MP
LFLAGS  =   $(CFLAGS) -lncurses
# IFLAGS
INCLUDES	= ./includes
IFLAGS			= $(addprefix -I, $(INCLUDES))
RM		=	rm -rf

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $$(dirname $@)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re