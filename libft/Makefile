NAME = libft.a

CC = cc
CFLAGS = -Wall -Werror -Wextra
 
SRCS = only_spaces.c ft_substr.c ft_strlen.c ft_strdup.c

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
