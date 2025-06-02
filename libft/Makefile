NAME = libft.a

CC = cc
CFLAGS = -g3
 #-Wall -Werror -Wextra
SRCS = only_spaces.c ft_substr.c ft_strlen.c ft_strdup.c ft_strcmp.c ft_strdup2.c \
       is_quote.c is_operator.c ft_strjoin.c strjoin_free.c ft_isalnum.c \
	   ft_strncmp.c ft_itoa.c ft_split.c ft_strchr.c ft_bzero.c ft_calloc.c \
	   ft_strndup.c ft_memdel.c ft_putendl_fd.c ft_putstr_fd.c ft_strcpy.c \
	   ft_putendl.c ft_atoi.c ft_strisnum.c ft_skip_spacenl.c free_split.c \
	   ft_isdigit.c ft_putstr.c ft_isspace.c ft_isalpha.c ft_atol.c

OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	ar -rcs $(NAME) $(OBJS)

${OBJS} : %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
