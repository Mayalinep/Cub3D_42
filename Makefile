# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/26 00:00:00 by mpelage           #+#    #+#              #
#    Updated: 2025/06/30 15:04:51 by mpelage          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'exécutable
NAME = cub3D

# Compilateur et flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3
MATH_FLAGS = -lm
INCLUDES = -I./include -I./minilibx-linux

# Chemins
SRC_DIR = src
OBJ_DIR = obj
MLX_DIR = minilibx-linux

# Fichiers sources
SRCS = main.c \
	$(SRC_DIR)/input/keyboard_utils.c \
	$(SRC_DIR)/input/movement.c \
	$(SRC_DIR)/input/rotation.c \
	$(SRC_DIR)/mlx/init_mlx.c \
	$(SRC_DIR)/parsing/simulation.c \
	$(SRC_DIR)/parsing/init.c \
	$(SRC_DIR)/parsing/verif.c \
	$(SRC_DIR)/parsing/mapping.c \
	$(SRC_DIR)/parsing/look.c \
	$(SRC_DIR)/parsing/utils.c \
	$(SRC_DIR)/parsing/utils_two.c \
	$(SRC_DIR)/parsing/utils_three.c \
	$(SRC_DIR)/parsing/utils_four.c \
	$(SRC_DIR)/raycasting/dda.c \
	$(SRC_DIR)/raycasting/raycasting_utils.c \
	$(SRC_DIR)/raycasting/raycasting.c \
	$(SRC_DIR)/rendering/draw.c \
	$(SRC_DIR)/rendering/textures.c \
	$(SRC_DIR)/utils/string_utils.c \
	GNL/get_next_line.c \
	GNL/get_next_line_utils.c

# Fichiers objets
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Bibliothèques MinilibX
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11

# Couleurs pour les messages
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
YELLOW = \033[0;33m
NC = \033[0m # No Color

# Règle principale
all: $(MLX_LIB) $(NAME)

# Compilation de l'exécutable
$(NAME): $(OBJS)
	@echo "$(BLUE)Linking $(NAME)...$(NC)"
	@$(CC) $(OBJS) $(MLX_FLAGS) $(MATH_FLAGS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(NC)"

# Compilation des fichiers objets
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compilation de la MinilibX
$(MLX_LIB):
	@echo "$(BLUE)Compiling MinilibX...$(NC)"
	@make -C $(MLX_DIR) > /dev/null 2>&1
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

# Tests et debug
debug: CFLAGS += -fsanitize=address -fsanitize=undefined
debug: re

# Règle pour lancer le programme avec une carte de test
test: $(NAME)
	@if [ -f maps/test.cub ]; then \
		echo "$(BLUE)Running $(NAME) with test map...$(NC)"; \
		./$(NAME) maps/test.cub; \
	else \
		echo "$(YELLOW)No test map found. Running $(NAME) without arguments...$(NC)"; \
		./$(NAME); \
	fi

# Règles qui ne correspondent pas à des fichiers
.PHONY: all clean fclean re debug test

# Règle d'aide
help:
	@echo "$(BLUE)Available targets:$(NC)"
	@echo "  $(GREEN)all$(NC)     - Compile the project"
	@echo "  $(GREEN)clean$(NC)   - Remove object files"
	@echo "  $(GREEN)fclean$(NC)  - Remove object files and executable"
	@echo "  $(GREEN)re$(NC)      - Recompile the project"
	@echo "  $(GREEN)debug$(NC)   - Compile with debugging flags"
	@echo "  $(GREEN)test$(NC)    - Run the program with test map"
	@echo "  $(GREEN)help$(NC)    - Display this help message"