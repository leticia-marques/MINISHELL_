NAME = minishell

SRC_DIR = ./src
PARSER_DIR = ./parser
AUX_DIR = ./aux

AUX_FILES = source_handler.c free.c init.c error.c exec_cmd.c find_path.c
AUX_FILES+= here_doc.c check_argv.c exec_utils.c
AUX_FILES+= var_expansion.c var_expansion_utils.c
AUX_FILES+= check_file.c call_funcs.c filter_cmd.c signals.c
AUX_FILES+= read_infile.c export.c unset.c export_utils.c cd.c exit_builtin.c
AUX_FILES+= check_echo.c syntax_error.c last_cmd.c
PARSER_FILES = scanner_utils.c tokenizer.c parser.c node.c set_value_str.c

AUX_PATH = $(addprefix $(AUX_DIR)/, $(AUX_FILES))
PARSER_PATH = $(addprefix $(PARSER_DIR)/, $(PARSER_FILES))

SRC = main.c $(PARSER_PATH) $(AUX_PATH)

OBJS = $(addprefix $(OBJS_DIR)/, $(SRC:.c=.o))
OBJS_DIR = objects

MKD = mkdir -p $(@D)
CC = gcc
CFLAGS = -Wall -Werror -Wextra -ggdb3 -g
RM  = rm -rf

LIBFT_PATH = Libft
LIB = -L$(LIBFT_PATH) -lft
INC = -I $(LIBFT_PATH) -I includes
READLINE = -L/usr/include -lreadline

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	$(MKD)
	$(CC) $(CFLAGS) $(READLINE) $(INC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	make all -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) $(READLINE) $(INC)  -o $(NAME)

clean:
	make clean -C $(LIBFT_PATH)
	$(RM) $(OBJS_DIR)

fclean: clean
		make fclean -C $(LIBFT_PATH)
		$(RM) $(NAME)

re: fclean all

run:
	make all
	./minishell

leak:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp --trace-children=yes --verbose --log-file=valgrind-out.txt ./$(NAME)
