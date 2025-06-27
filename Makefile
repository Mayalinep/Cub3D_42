# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/26 00:00:00 by mpelage           #+#    #+#              #
#    Updated: 2025/06/27 14:32:14 by ssoukoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'exécutable
NAME = cub3D

# Compilateur et flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3
MATH_FLAGS = -lm
INCLUDES = -I./include -I./minilibx-linux -I./GNL -I./src

# Répertoires
SRC_DIR = src
GNL_DIR = GNL
OBJ_DIR = obj
MLX_DIR = minilibx-linux

# Détection automatique des fichiers sources
SRC_FILES = $(wildcard $(SRC_DIR)/**/*.c) $(wildcard $(SRC_DIR)/*.c)
	
GNL_FILES = $(wildcard $(GNL_DIR)/*.c)
ALL_SRCS = $(SRC_FILES) $(GNL_FILES)

# Génération des fichiers objets
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(ALL_SRCS))

# Bibliothèques MinilibX
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# Couleurs
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
YELLOW = \033[0;33m
NC = \033[0m

# Règle principale
all: $(MLX_LIB) $(NAME)

# Compilation de l'exécutable
$(NAME): $(OBJS)
	@echo "$(BLUE)Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(MLX_FLAGS) $(MATH_FLAGS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(NC)"

# Compilation des fichiers objets
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compilation de la MinilibX
$(MLX_LIB):
	@echo "$(BLUE)Compiling MinilibX...$(NC)"
	@make -C $(MLX_DIR)
	@echo "$(GREEN)✓ MinilibX compiled successfully!$(NC)"

# Nettoyage des fichiers objets
clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -rf $(OBJ_DIR)
	@make -C $(MLX_DIR) clean > /dev/null 2>&1
	@echo "$(GREEN)✓ Clean completed!$(NC)"

# Nettoyage complet
fclean: clean
	@echo "$(RED)Removing executable...$(NC)"
	@rm -f $(NAME)
	@echo "$(GREEN)✓ Full clean completed!$(NC)"

# Recompilation complète
re: fclean all

# Compilation avec debug (ASAN + UBSAN)
debug: CFLAGS += -fsanitize=address -fsanitize=undefined
debug: re

# Exécution de test
test: $(NAME)
	@if [ -f maps/test.cub ]; then \
		echo "$(BLUE)Running $(NAME) with test map...$(NC)"; \
		./$(NAME) maps/test.cub; \
	else \
		echo "$(YELLOW)No test map found. Running $(NAME) without arguments...$(NC)"; \
		./$(NAME); \
	fi

# Règles phony
.PHONY: all clean fclean re debug test help

# Aide
help:
	@echo "$(BLUE)Available targets:$(NC)"
	@echo "  $(GREEN)all$(NC)     - Compile the project"
	@echo "  $(GREEN)clean$(NC)   - Remove object files"
	@echo "  $(GREEN)fclean$(NC)  - Remove object files and executable"
	@echo "  $(GREEN)re$(NC)      - Recompile the project"
	@echo "  $(GREEN)debug$(NC)   - Compile with debug flags"
	@echo "  $(GREEN)test$(NC)    - Run with t
