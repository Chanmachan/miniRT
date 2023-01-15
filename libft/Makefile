NAME = libft.a

SRCS_DIR = ./srcs

OBJS_DIR = ./objs

SRCS_FILE = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
            ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
            ft_split.c ft_strchr.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
            ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
            ft_strdup.c ft_calloc.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
            ft_putendl_fd.c ft_putnbr_fd.c ft_min.c ft_max.c

SRCS = $(addprefix $(SRCS_DIR)/,$(SRCS_FILE))

LIBFT = ./srcs

INCLUDES = ./srcs/libft.h

OBJS = $(patsubst $(SRCS_DIR)/%, $(OBJS_DIR)/%, $(SRCS:.c=.o))

CFLAGS = -Wall -Wextra -Werror
#-MP -MMD

all: $(OBJS_DIR) $(NAME)

$(OBJS_DIR) :
		mkdir -p $(OBJS_DIR)

$(NAME) : $(OBJS)
		ar rcs $(NAME) $(OBJS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) -r $(OBJS_DIR)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re