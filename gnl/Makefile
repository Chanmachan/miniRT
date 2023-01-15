NAME = gnl.a

SRCS_DIR = ./srcs

OBJS_DIR = ./objs

SRCS_FILE = get_next_line.c get_next_line_utils.c

SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILE))

INCLUDES = get_next_line.h

OBJS = $(patsubst $(SRCS_DIR)/%, $(OBJS_DIR)/%, $(SRCS:.c=.o))

CFLAGS = -Wall -Wextra -Werror

all: $(OBJS_DIR) $(NAME)

$(OBJS_DIR):
		mkdir -p $(OBJS_DIR)

$(NAME): $(OBJS)
		ar rcs $(NAME) $(OBJS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) -r $(OBJS_DIR)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re