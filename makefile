NAME = minishell

INC = ./include/minishell.h  \
	libft/libft.h

READLINE = $(shell brew --prefix readline)
RM = rm -rf
INCLUDE_READLINE = $(addprefix $(READLINE),/include)

LIB_READLINE = $(addprefix $(READLINE),/lib)
FILES_SRC = src
FILES_UT = $(FILES_SRC)
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a 



CC = cc -Wall -Wextra -Werror 

SRC =$(FILES_SRC)/main.c \
	$(FILES_SRC)/readline.c \
	$(FILES_SRC)/lexer.c \
	$(FILES_SRC)/lexer_utils.c \
	$(FILES_SRC)/token_utils.c \
	$(FILES_SRC)/parser.c \
	$(FILES_SRC)/red_utils.c \
	$(FILES_SRC)/parser_utils.c \
	$(FILES_SRC)/expander_value.c \
	$(FILES_SRC)/check_errors.c \
	$(FILES_SRC)/env_utils.c \
	$(FILES_SRC)/execution/reset_io.c \
	$(FILES_SRC)/open_herdoc.c \
	$(FILES_SRC)/execution/exuc_commond.c \
	$(FILES_SRC)/execution/print_error.c \
	$(FILES_SRC)/execution/builtin/ft_cd.c \
	$(FILES_SRC)/execution/builtin/ft_export.c \
	$(FILES_SRC)/execution/builtin/ft_export2.c \
	$(FILES_SRC)/execution/builtin/ft_export3.c \
	$(FILES_SRC)/execution/builtin/ft_echo.c \
	$(FILES_SRC)/execution/builtin/ft_pwd.c \
	$(FILES_SRC)/execution/builtin/ft_env.c \
	$(FILES_SRC)/execution/builtin/ft_unset.c \
	$(FILES_SRC)/execution/builtin/ft_exit.c


	



OBJ = $(SRC:.c=.o)

%.o : %.c
	$(CC) -I $(INCLUDE_READLINE) -c $< -o $@

all : $(NAME)

$(NAME) : $(INC)  $(OBJ) $(LIBFT_LIB)
	$(CC)  -I $(INCLUDE_READLINE) -L $(LIB_READLINE) -lreadline $(LIBFT_LIB) $(OBJ) -o $(NAME)

$(LIBFT_LIB) :
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJ)
	$(MAKE) clean -C $(LIBFT_DIR)
fclean : clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)
re: fclean all
