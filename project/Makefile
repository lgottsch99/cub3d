# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 16:00:38 by lgottsch          #+#    #+#              #
#    Updated: 2025/06/12 16:22:53 by lgottsch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#default make => linux
#make mac = compilation macOs

NAME = cub3D

# directories
LIBFTDIR= ./lib/full_libft
MLXDIR= ./lib/mlx_linux
MLXMACDIR= ./lib/mlx_mac
SRC_REND_FOLDER = ./src/rendering/
SRC_DIR = src

CC = cc 
CFLAGS = -Wall -Wextra -Werror

MLX_FLAGS_LX = -I/usr/X11/include -L/usr/X11/lib -lX11 -lXext -lm -g
MLX_FLAGS_MAC = -L$(MLXMACDIR) -lmlx -framework OpenGL -framework AppKit
LIBFT_FLAGS_MAC = -L$(LIBFTDIR) -lfull_libft

MLX_INC_MAC = -I$(MLXMACDIR)

SRC= $(SRC_DIR)/main.c \
	$(SRC_DIR)/parser/init_map.c \
	$(SRC_DIR)/parser/parse_data.c \
	$(SRC_DIR)/parser/valid_data.c \
	$(SRC_DIR)/parser/process_line.c \
	$(SRC_DIR)/utilis/free_function.c \
	$(SRC_DIR)/utilis/parser_color_utilis.c \
	$(SRC_DIR)/utilis/parser_utilis.c \
	$(SRC_DIR)/utilis/is_extension_valid.c \
	$(SRC_DIR)/utilis/validate_utilis.c \
	$(SRC_DIR)/utilis/validate_map_utilis.c \
	$(SRC_DIR)/validator/validate_data.c\
	$(SRC_DIR)/validator/map_check.c \
	$(SRC_REND_FOLDER)raycasting.c \
	$(SRC_REND_FOLDER)utils.c \
	$(SRC_REND_FOLDER)minimap.c \
	$(SRC_REND_FOLDER)raycast_utils.c \
	$(SRC_REND_FOLDER)hooks.c \
	$(SRC_REND_FOLDER)vector_math.c \
	$(SRC_REND_FOLDER)player_movement.c \
	$(SRC_REND_FOLDER)minimap_utils.c \
	$(SRC_REND_FOLDER)game_init.c \
	$(SRC_REND_FOLDER)dda.c \
	$(SRC_REND_FOLDER)texture_utils.c \
	$(SRC_REND_FOLDER)boundary_check.c 

OBJ = $(SRC:.c=.o)

# lib files
LIBFTA= $(LIBFTDIR)/libfull_libft.a
MLXA= $(MLXDIR)/libmlx_Linux.a

# rules

$(NAME): libft mlx-linux
	@ $(CC) $(CFLAGS) $(SRC) $(LIBFTA) $(MLXA) -o $(NAME) $(MLX_FLAGS_LX)

libft:
	@make -C $(LIBFTDIR)
	@make clean -C $(LIBFTDIR)

mlx-linux: 
	cd $(MLXDIR) && ./configure

all: $(NAME)

clean:
	rm -f $(OBJ)
	@cd $(LIBFTDIR) && make clean
	@cd $(MLXDIR) && make clean
	@cd $(MLXMACDIR) && make clean


fclean: clean
	rm -f $(NAME)
	@cd $(LIBFTDIR) && make clean
	@cd $(MLXDIR) && make clean

re: fclean all

norm:
	norminette $(SRC) $(LIBFTDIR)

# compilation on mac
mac: libft mlx-mac
	@$(CC) $(CFLAGS) $(SRC) $(LIBFTA) -o $(NAME) $(MLX_FLAGS_MAC) $(MLX_INC_MAC) $(LIBFT_FLAGS)
	@mv $(MLXMACDIR)/libmlx.dylib ./ || true

mlx-mac:
	@make -C $(MLXMACDIR)

.PHONY: all clean fclean re libft mlx-linux mac norm mlx-mac