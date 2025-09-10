# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samalves <samalves@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/23 16:24:44 by samalves          #+#    #+#              #
#    Updated: 2025/06/23 17:27:45 by samalves         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCDIR = srcs
INCDIR = includes
OBJDIR = objs

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I$(INCDIR)

SRCS =	ft_printf.c \
		ft_decimal.c \
		ft_hexupp.c \
		ft_hexlow.c \
		ft_phex.c \
		ft_unsdecimal.c \
		ft_putstr.c \
		ft_putchar.c

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

HEADERS = $(INCDIR)/libftprintf.h

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Archiving $(NAME)...$(RESET)"
	@ar rcs $@ $^
	@echo "$(GREEN)✓ $(NAME) created successfully!$(RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS) | $(OBJDIR)
	@mkdir -p $(dir $@)
	@echo "$(GREEN)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJDIR)
	@echo "$(RED)✓ Object files cleaned!$(RESET)"

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@echo "$(RED)✓ $(NAME) removed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re

.PRECIOUS: $(OBJDIR)/%.o
