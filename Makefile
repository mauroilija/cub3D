# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abita <abita@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/11 14:58:16 by abita             #+#    #+#              #
#    Updated: 2026/04/28 19:34:12 by abita            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += --no-print-directory
NAME = cub3D

CC = cc 
CFLAGS = -Wall -Werror -Wextra -g
LIBS = -lmlx -lX11 -lXext -lm

SRCS = \
	  src/main.c \
	  src/mlx/key/keys.c \
	  src/mlx/window/window.c \
	  src/utils/map_utils.c \
	  src/utils/parse_utils.c \
	  src/utils/other_utils.c \
	  src/utils/color_utils.c \
	  src/utils/texture_utils.c \
	  src/parser/parser.c \
	  src/parser/parse_map.c \
	  src/parser/parse_color.c \
	  src/parser/parse_texture.c \
	  src/mlx/init_player/player.c \
	  src/mlx/dda/dda_utils.c \
	  src/mlx/dda/dda_loop.c  \
	  src/mlx/dda/render.c \
	  src/mlx/textures/textures.c \
	  src/mlx/movement/movement.c \
	  src/mlx/textures/texture_utils.c \
	  src/mlx/color/colors.c 

OBJ = $(SRCS:.c=.o)

LIBFT_DIR = inc/Libft
LIBFT = $(LIBFT_DIR)/libft.a

SILENT ?=0
GREEN = \033[0;32m
PURPLE = \033[1;35m
CYAN = \033[0;36m
RED = \033[1;31m
RESET = \033[0m

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	@if [ "$(SILENT)" = "0" ]; then echo "$(GREEN)compiling...$(RESET)"; fi
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIBS) -o $(NAME)
	@if [ "$(SILENT)" = "0" ]; then  echo "$(GREEN)ready to execute$(RESET)"; fi

clean:
	@if [ "$(SILENT)" = "0" ]; then echo "$(CYAN)deleting object files...$(RESET)"; fi
	@rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@if [ "$(SILENT)" = "0" ]; then echo "$(CYAN)done$(RESET)"; fi
fclean: clean
	@if [ "$(SILENT)" = "0" ]; then echo "$(RED)fully cleaning...$(RESET)"; fi
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@if [ "$(SILENT)" = "0" ]; then echo "$(RED)done$(RESET)"; fi
re:
	@echo "$(GREEN)re(making)...$(RESET)"
	@$(MAKE) SILENT=1 fclean
	@$(MAKE) SILENT=1 all
	@echo "$(GREEN)done, ready to execute again$(RESET)"

.PHONY: all clean fclean re
