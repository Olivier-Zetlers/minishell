# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: student <student@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/01 00:00:00 by student          #+#    #+#              #
#    Updated: 2025/12/08 20:12:59 by ozetlers         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I./includes
LIBS		= -lreadline

# Source files organized by module
SRCS_MAIN	= srcs/main.c \
			  srcs/shell_init.c \
			  srcs/shell_loop.c \
			  srcs/shell_cleanup.c \
			  srcs/input_reader.c

SRCS_LEXER	= srcs/lexer/lexer.c \
			  srcs/lexer/lexer_utils.c \
			  srcs/lexer/lexer_helpers.c \
			  srcs/lexer/token_list.c \
			  srcs/lexer/quote_handler.c \
			  srcs/lexer/operator_detector.c

SRCS_PARSER	= srcs/parser/parser.c \
			  srcs/parser/parser_utils.c \
			  srcs/parser/command_builder.c \
			  srcs/parser/redirect_parser.c \
			  srcs/parser/syntax_checker.c

SRCS_EXPAND	= srcs/expander/expander.c \
			  srcs/expander/variable_expand.c \
			  srcs/expander/quote_removal.c \
			  srcs/expander/field_split.c \
			  srcs/expander/expansion_utils.c \
			  srcs/expander/split_quoted_token.c \
			  srcs/expander/argv_expansion.c

SRCS_EXEC	= srcs/executor/executor.c \
			  srcs/executor/executor_utils.c \
			  srcs/executor/executor_single_utils.c \
			  srcs/executor/executor_cleanup.c \
			  srcs/executor/pipeline_exec.c \
			  srcs/executor/path_resolver.c \
			  srcs/executor/process_manager.c \
			  srcs/executor/process_utils.c \
			  srcs/executor/pipe_handler.c \
			  srcs/executor/path_errors.c \
			  srcs/executor/exec_error_handler.c

SRCS_REDIR	= srcs/redirections/redirect_handler.c \
			  srcs/redirections/heredoc.c \
			  srcs/redirections/heredoc_helpers.c \
			  srcs/redirections/fd_manager.c \
			  srcs/redirections/redirect_utils.c

SRCS_BUILTIN = srcs/builtins/builtin_echo.c \
			   srcs/builtins/builtin_cd.c \
			   srcs/builtins/builtin_pwd.c \
			   srcs/builtins/builtin_export.c \
			   srcs/builtins/builtin_unset.c \
			   srcs/builtins/builtin_env.c \
			   srcs/builtins/builtin_exit.c \
			   srcs/builtins/builtin_utils.c

SRCS_SIGNAL	= srcs/signals/signal_handler.c \
			  srcs/signals/signal_utils.c

SRCS_ENV	= srcs/environment/env_manager.c \
			  srcs/environment/env_utils.c \
			  srcs/environment/env_getset.c

SRCS_UTILS	= srcs/utils/string_utils.c \
			  srcs/utils/string_utils2.c \
			  srcs/utils/string_utils3.c \
			  srcs/utils/memory_utils.c \
			  srcs/utils/error_handler.c \
			  srcs/utils/ft_substr.c

SRCS		= $(SRCS_MAIN) $(SRCS_LEXER) $(SRCS_PARSER) $(SRCS_EXPAND) \
			  $(SRCS_EXEC) $(SRCS_REDIR) $(SRCS_BUILTIN) $(SRCS_SIGNAL) \
			  $(SRCS_ENV) $(SRCS_UTILS)

OBJS		= $(SRCS:.c=.o)

# Colors for output
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
RESET		= \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)
	@echo "$(GREEN)$(NAME) created successfully!$(RESET)"

%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(YELLOW)Removing object files...$(RESET)"
	@rm -f $(OBJS)
	@echo "$(GREEN)Clean complete!$(RESET)"

fclean: clean
	@echo "$(YELLOW)Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)Full clean complete!$(RESET)"

re: fclean all

norm:
	@echo "$(YELLOW)Running norminette...$(RESET)"
	@norminette srcs/ includes/

.PHONY: all clean fclean re norm
