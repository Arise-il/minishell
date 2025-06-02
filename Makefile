NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LDFLAGS = -lreadline
#-fsanitize=address  
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = src/main.c src/parser/parser.c src/signals/signals.c src/signals/signals_utils.c \
       src/utils/memory_utils.c src/parser/tokenizer.c src/parser/tokenizer_utils.c \
	   src/parser/syntax_checker.c src/parser/cmd_builder.c src/parser/expander.c src/parser/expander_utils.c \
	   src/parser/heredoc.c src/execution/builtins/cd.c src/execution/builtins/echo.c src/execution/builtins/env.c \
	   src/execution/builtins/exit.c src/execution/builtins/export.c src/execution/builtins/pwd.c \
	   src/execution/builtins/unset.c src/execution/execution.c src/execution/builtins.c src/utils/memory_utils2.c \
	   src/env/env.c src/env/get_env.c src/env/shlvl.c src/env/sort_env.c src/execution/free.c \

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
