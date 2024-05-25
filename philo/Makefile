# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/22 15:47:45 by ribana-b          #+#    #+# Malaga       #
#    Updated: 2024/05/24 13:39:40 by ribana-b         ###   ########.com       #
#                                                                              #
# **************************************************************************** #

# @--------------------------------------------------------------------------@ #
# |                                 Colors                                   | #
# @--------------------------------------------------------------------------@ #

T_BLACK = \033[30m
T_RED = \033[31m
T_GREEN = \033[32m
T_YELLOW = \033[33m
T_BLUE = \033[34m
T_MAGENTA = \033[35m
T_CYAN = \033[36m
T_WHITE = \033[37m
T_CUSTOM = \033[38;2;183;72;214m

BOLD = \033[1m
ITALIC = \033[3m
UNDERLINE = \033[4m
STRIKETHROUGH = \033[5m

CLEAR_LINE = \033[1F\r\033[2K

RESET = \033[0m

# @--------------------------------------------------------------------------@ #
# |                                 Macros                                   | #
# @--------------------------------------------------------------------------@ #

NAME = philo

CC = cc

ifdef WITH_DEBUG
CFLAGS = -Wall -Wextra -Werror -ggdb
else ifdef WITH_DEBUG_THREAD
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread
else
CFLAGS = -Wall -Wextra -Werror
endif

CPPFLAGS = -I./include
LDLIBS = -pthread

RM = rm -rf

SRC_DIR = ./
UTILS_DIR = ./
OBJ_DIR = obj/

SRC_FILES = main.c
UTILS_FILES = initialise.c error.c libc.c

INCLUDE_FILE = philosophers.h

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
UTILS = $(addprefix $(UTILS_DIR), $(UTILS_FILES))

OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC)) \
		$(patsubst $(UTILS_DIR)%.c, $(OBJ_DIR)%.o, $(UTILS)) \

COMPILE_MSG = @echo "$(CLEAR_LINE)🧩 🦔 $(T_WHITE)$(BOLD)Compiling $(ITALIC)$<$(RESET)"
OBJ_MSG = @echo "✅ 🦔 $(T_YELLOW)$(BOLD)Objects $(RESET)$(T_GREEN)created successfully!$(RESET)"
OUTPUT_MSG = @echo "✅ 🦔 $(T_CUSTOM)$(BOLD)$(ITALIC)$(NAME) $(RESET)$(T_GREEN)created successfully!$(RESET)"
CLEAN_MSG = @echo "🗑️  🦔 $(T_YELLOW)$(BOLD)Objects $(RESET)$(T_RED)destroyed successfully!$(RESET)"
FCLEAN_MSG = @echo "🗑️  🦔 $(T_MAGENTA)$(BOLD)$(ITALIC)$(NAME) $(RESET)$(T_RED)destroyed successfully!$(RESET)"

# @--------------------------------------------------------------------------@ #
# |                                 Targets                                  | #
# @--------------------------------------------------------------------------@ #

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDE_FILE)
	$(OBJ_MSG)
	@$(CC) -o $(NAME) $(CFLAGS) $(CPPFLAGS) $(OBJ)
	$(OUTPUT_MSG)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(COMPILE_MSG)
	@$(CC) -o $@ $(CFLAGS) $(CPPFLAGS) $(LDLIBS) -c $<

$(OBJ_DIR)%.o: $(UTILS_DIR)%.c | $(OBJ_DIR)
	$(COMPILE_MSG)
	@$(CC) -o $@ $(CFLAGS) $(CPPFLAGS) $(LDLIBS) -c $<

clean:
	@$(RM) $(OBJ_DIR)
	$(CLEAN_MSG)

fclean: clean
	@$(RM) $(NAME)
	$(FCLEAN_MSG)

re:
	@make -s fclean
	@make -s all

run: $(NAME)
	@./$(NAME) $(ARGS)

debug: fclean
	@make -s WITH_DEBUG=1

debug_thread: fclean
	@make -s WITH_DEBUG_THREAD=1

tags:
	@$(shell find . -path ./bonus_part -prune -o -print -type f \( -name "*c" -o -name "*.h" \) > temp)
	@ctags -F $(shell cat temp)
	@$(RM) temp

.PHONY: all clean debug debug_thread fclean re run tags
