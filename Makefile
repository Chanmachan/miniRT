NAME = miniRT

SRCS_DIR = ./srcs

OBJS_DIR = ./objs

SRCS_FILE = main.c \
			utils.c \
			vec.c \
			init.c \
			raytrace.c

SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILE))

LIBFT_DIR = ./libft
GNL_DIR = ./gnl
MLX_DIR = ./minilibx-linux

INCLUDES = ./includes/

OBJS = $(patsubst $(SRCS_DIR)/%, $(OBJS_DIR)/%, $(SRCS:.c=.o))

LIBFT_ARC = ./libft/libft.a
LIBGNL = ./gnl/gnl.a
CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g

os = $(shell uname)

ifeq ($(os), Darwin)
	LIBMLX = ./minilibx-linux/libmlx.a ./minilibx-linux/libmlx_Darwin.a
	MLXFLAGS +=  -L/usr/X11R6/lib -lX11 -lXext -framework OpenGL -framework AppKit #-fsanitize=address
else
	LIBMLX = minilibx-linux/libmlx.a minilibx-linux/libmlx_Linux.a -lXext -lX11 -lm
	MLXFLAGS +=
endif

#CFLAGS = -Wall -Werror -Wextra

#need#
#CFLAGS = -Wall -Werror -Wextra
#LIBMLX = ./minilibx-linux/libmlx.a ./minilibx-linux/libmlx_Darwin.a
#MLXFLAGS = -L/usr/X11R6/lib -lX11 -lXext -framework OpenGL -framework AppKit #-fsanitize=address
#-fsanitize=address
#MP -MMD

all: $(NAME)

$(NAME): $(OBJS)
		$(MAKE) -C $(LIBFT_DIR)
		$(MAKE) -C $(GNL_DIR)
		$(MAKE) -C $(MLX_DIR)
		$(CC) $(CFLAGS) $(MLXFLAGS) $^ -o $(NAME) $(LIBFT_ARC) $(LIBGNL) $(LIBMLX)
#$(CC) $(CFLAGS) $(LIBGNL) $(LIBMLX) $(LIBFT_ARC) $< -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
		mkdir -p $(OBJS_DIR)
		$(CC) $(CFLAGS) -c $< -o $@
#$(CC) $(CFLLAGS) -c $< -o $@

clean:
		$(RM) -r $(OBJS_DIR)
		$(MAKE) -C $(LIBFT_DIR) clean
		$(MAKE) -C $(GNL_DIR) clean
		$(MAKE) -C $(MLX_DIR) clean

fclean: clean
		$(MAKE) -C $(LIBFT_DIR) fclean
		$(MAKE) -C $(GNL_DIR) fclean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re