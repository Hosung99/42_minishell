CC = cc
CFLAGS = -Wall -Werror -Wextra
NAME = minishell
SRCS = main.c parsing/set_term.c parsing/set_signal.c parsing/print_picture.c parsing/parse.c parsing/set_token_type.c parsing/ft_split_index.c parsing/make_token.c parsing/set_quote.c parsing/ft_strtrim_index.c parsing/set_envp.c parsing/ft_search_envp_key.c parsing/set_cmd.c parsing/free_cmd.c parsing/ft_is_metachar.c parsing/ft_strjoin_char.c parsing/make_cmd.c parsing/delete_quote.c parsing/before_check.c parsing/ft_split_pipe.c parsing/set_init.c\
./builtin/builtin.c ./builtin/cd.c ./builtin/echo.c ./builtin/env.c ./builtin/exit.c ./builtin/export.c ./builtin/pwd.c ./builtin/unset.c \
./executor/cmd.c ./executor/executor.c ./executor/init_info.c ./executor/open.c ./executor/path.c ./executor/process.c ./executor/wait.c ./executor/here_doc.c ./executor/free.c \
./executor/error.c ./executor/envp.c ./executor/here_doc_util.c

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
