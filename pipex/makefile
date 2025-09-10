# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samalves <samalves@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/10 23:46:42 by samalves          #+#    #+#              #
#    Updated: 2025/09/10 23:47:41 by samalves         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g

NAME		= pipex

SRC_DIR		= src
UTILS_DIR	= utils
INC_DIR		= includes
PRINTF_DIR	= ft_printf
OBJ_DIR		= obj

SRC_FILES	= main.c pipex.c
UTILS_FILES	= ft_free.c ft_split.c ft_strncmp.c ft_substr.c ft_strlen.c ft_strdup.c ft_strjoin.c

SRCS		= $(addprefix $(SRC_DIR)/, $(SRC_FILES)) \
			  $(addprefix $(UTILS_DIR)/, $(UTILS_FILES))

OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)

PRINTF		= $(PRINTF_DIR)/libftprintf.a

INCLUDES	= -I$(INC_DIR) -I$(PRINTF_DIR)/includes

GREEN		= \033[0;32m
YELLOW		= \033[0;33m
RED			= \033[0;31m
BLUE		= \033[0;34m
CYAN		= \033[0;36m
RESET		= \033[0m

all: $(PRINTF) $(NAME)

$(NAME): $(OBJS) $(PRINTF)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(PRINTF) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) created successfully!$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)Compiling $(notdir $<)...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(PRINTF):
	@echo "$(CYAN)Building ft_printf...$(RESET)"
	@$(MAKE) -C $(PRINTF_DIR) --no-print-directory

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(PRINTF_DIR) clean --no-print-directory

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C $(PRINTF_DIR) fclean --no-print-directory

re: fclean all
