# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/05 12:27:26 by ssoukoun          #+#    #+#              #
#    Updated: 2025/06/10 20:27:28 by ssoukoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#                                 VARIABLES                                   #
# **************************************************************************** #

NAME        = cub3D
CC          = cc
CFLAGS      = -g3 -Wall -Werror -Wextra

HEAD        = .
SRC_DIR     = ./src
GNL_DIR     = ./GNL
OBJ_DIR     = ./obj
MLX_DIR     = ./minilibx-linux

MLX_FLAGS   = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
INCLUDES    = -I$(HEAD) -I$(SRC_DIR) -I$(GNL_DIR) -I$(MLX_DIR)

SRC_FILES   = $(wildcard $(SRC_DIR)/*.c)
GNL_FILES   = $(wildcard $(GNL_DIR)/*.c)

SRC_OBJS    = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
GNL_OBJS    = $(patsubst $(GNL_DIR)/%.c, $(OBJ_DIR)/%.gnl.o, $(GNL_FILES))

OBJS        = $(SRC_OBJS) $(GNL_OBJS)

# **************************************************************************** #
#                                 RULES                                       #
# **************************************************************************** #

all: $(MLX_DIR)/libmlx.a $(NAME)

$(MLX_DIR)/libmlx.a:
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.gnl.o: $(GNL_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
