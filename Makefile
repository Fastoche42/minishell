# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #\
#                                                     +:+ +:+         +:+      #
#    By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/28 16:07:42 by fl-hote            #+#    #+#              #
#    Updated: 2022/12/15 12:59:46 by fl-hote          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = Libft/libft.a

HOST := $(shell hostname)
ifeq ($(HOST), LAPTOP-M60DL66F)
	CPPFLAGS =
	LDFLAGS = -lreadline
	CFLAG = -Wall -Wextra -lreadline
else
	CPPFLAGS = -I/Users/$(USER)/.brew/opt/readline/include 
	LDFLAGS = -L/Users/$(USER)/.brew/opt/readline/lib -lreadline
	CFLAG = -Wall -Wextra -Werror -g
endif

SRCS =	srcs/main.c\
		srcs/init_struct.c\
		srcs/pipex.c\
		srcs/cmd_path.c\
		srcs/redirection.c\
		srcs/file_handler.c

CHECK =	check/error_manager.c\
		
BUILTINS =	builtins/exec_cd.c\
			builtins/exec_echo.c\
			builtins/exec_env.c\
			builtins/exec_exit.c\
			builtins/exec_export.c\
			builtins/exec_export2.c\
			builtins/exec_pwd.c\
			builtins/exec_unset.c
	  
UTILS =	utils/close_fds.c\
		utils/exit.c\
		utils/build_envp.c\
		utils/is_builtin.c\
		utils/var_handler.c\
		utils/var_handler2.c

PARSING =	parsing/parsing.c\
			parsing/split_token.c\
			parsing/set_redir.c\
			parsing/pars_quotes.c\
			parsing/parsing_utils.c

EXEC =	exec/signal.c\
		exec/which_command.c

ALL_SRCS =	$(SRCS)\
			$(CHECK)\
			$(BUILTINS)\
			$(UTILS)\
			$(PARSING)\
			$(EXEC)

OBJS = $(ALL_SRCS:.c=.o)

RE_LIBFT = @make -C Libft

all : $(NAME)

alln : all
		norminette

.c.o:
	@cc -o $@ -c $< $(CPPFLAGS) $(CFLAG) 

$(NAME) : $(OBJS)
		$(RE_LIBFT)
		@cc -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)
		@echo "$(GREEN)$(BOLD)Minishell Executable Created$(NORM)"
clean :
		@rm -rf $(OBJS)
		@make clean -C Libft
		@echo "$(GREEN)$(BOLD)Minishell objects removed$(NORM)"

fclean : clean
		@rm -rf $(NAME)
		@make fclean -C Libft
		@echo "$(GREEN)$(BOLD)Executable removed$(NORM)"

re : fclean all

#----------------------COLORS----------------------
GREEN=\x1b[32m
BOLD=\033[1m
NORM=\033[0m

.PHONY: all alln clean fclean re
