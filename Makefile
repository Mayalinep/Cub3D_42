# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/26 14:41:00 by mpelage           #+#    #+#              #
#    Updated: 2025/06/26 14:54:20 by mpelage          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = gcc
FLAGS = -Wall -Wextra -Werror
MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
OBJ_DIR = obj

# Colors for progress bar
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
RED = \033[31m
RESET = \033[0m
BOLD = \033[1m

# Progress indicators
PROGRESS_1 = $(GREEN)[$(BOLD)✓$(RESET)$(GREEN)]$(RESET)
PROGRESS_2 = $(YELLOW)[$(BOLD)⟳$(RESET)$(YELLOW)]$(RESET)
PROGRESS_3 = $(BLUE)[$(BOLD)⚡$(RESET)$(BLUE)]$(RESET)
PROGRESS_4 = $(GREEN)[$(BOLD)🎯$(RESET)$(GREEN)]$(RESET)

# Main source files
SRCS = main.c

# Parsing source files
SRCS += src/parsing/simulation.c

# Rendering source files
SRCS += src/rendering/draw.c

# Input source files
SRCS += src/input/movement.c
SRCS += src/input/keyboard_utils.c
SRCS += src/input/rotation.c

# MLX source files
SRCS += src/mlx/init_mlx.c

# Raycasting source files
SRCS += src/raycasting/raycasting.c
SRCS += src/raycasting/raycasting_utils.c
SRCS += src/raycasting/dda.c

# Utils source files
SRCS += src/utils/string_utils.c

# Object files with obj/ prefix
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# Include directories
INCLUDES = -Iinclude -I$(MLX_DIR)

# Count total files for progress
TOTAL_FILES = $(words $(SRCS))
CURRENT_FILE = 0

# Default target
all: progress_start $(NAME) progress_end

# Progress start message
progress_start:
	@echo "$(BOLD)$(BLUE)╔══════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(BOLD)$(BLUE)║                    $(GREEN)Cub3D Compilation$(BLUE)                    ║$(RESET)"
	@echo "$(BOLD)$(BLUE)╚══════════════════════════════════════════════════════════════╝$(RESET)"
	@echo "$(YELLOW)📁 Creating directories...$(RESET)"

# Progress end message
progress_end:
	@echo "$(GREEN)$(BOLD)╔══════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(GREEN)$(BOLD)║                    $(BOLD)✅ Compilation Complete!$(GREEN)                    ║$(RESET)"
	@echo "$(GREEN)$(BOLD)╚══════════════════════════════════════════════════════════════╝$(RESET)"

# Create object directory structure
$(OBJ_DIR):
	@echo "$(PROGRESS_1) Directories created successfully"
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/src/parsing
	@mkdir -p $(OBJ_DIR)/src/rendering
	@mkdir -p $(OBJ_DIR)/src/input
	@mkdir -p $(OBJ_DIR)/src/mlx
	@mkdir -p $(OBJ_DIR)/src/raycasting
	@mkdir -p $(OBJ_DIR)/src/utils

# Build the executable
$(NAME): $(OBJS) $(MLX_LIB)
	@echo "$(YELLOW)🔗 Linking objects...$(RESET)"
	@$(CC) $(FLAGS) $(OBJS) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)
	@echo "$(PROGRESS_4) $(BOLD)$(NAME)$(RESET) executable created"

# Build MLX library
$(MLX_LIB):
	@echo "$(YELLOW)📚 Building MLX library...$(RESET)"
	@$(MAKE) -C $(MLX_DIR) > /dev/null 2>&1
	@echo "$(PROGRESS_1) MLX library ready"

# Compile source files to object files with progress
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(eval CURRENT_FILE := $(shell echo $$(($(CURRENT_FILE) + 1))))
	@echo "$(PROGRESS_2) Compiling $(BOLD)$<$(RESET) [$(CURRENT_FILE)/$(TOTAL_FILES)]"
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

# Clean object files
clean:
	@echo "$(YELLOW)🧹 Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(MLX_DIR) clean > /dev/null 2>&1
	@echo "$(PROGRESS_1) Clean completed"

# Clean everything
fclean: clean
	@echo "$(YELLOW)🗑️  Removing executable...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C $(MLX_DIR) fclean > /dev/null 2>&1
	@echo "$(PROGRESS_1) Full clean completed"

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re progress_start progress_end