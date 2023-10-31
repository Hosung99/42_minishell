CC = cc
CFLAGS = -Wall -Werror -Wextra -g
NAME = minishell
SRCS = main.c parsing/set_term.c parsing/set_signal.c parsing/print_picture.c parsing/parse.c parsing/set_token_type.c parsing/ft_split_index.c parsing/make_token.c parsing/set_quote.c parsing/ft_strtrim_index.c parsing/set_envp.c parsing/ft_search_envp_key.c
OBJS = $(SRCS:.c=.o)
LIBFT = ./libft/libft.a

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT) -lreadline

clean:
	make clean -C libft
	rm -f $(OBJS)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re