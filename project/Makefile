# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 16:00:38 by lgottsch          #+#    #+#              #
#    Updated: 2025/05/04 18:24:57 by lgottsch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#TO DO TEST
#default make => linux
#make mac = compilation macOs

NAME = cub3D

# directories
LIBFTDIR= ./lib/full_libft
MLXDIR= ./lib/mlx_linux
MLXMACDIR= ./lib/mlx_mac
SRC_FOLDER = ./src/

CC = cc 
CFLAGS = -Wall -Wextra -Werror

MLX_FLAGS_LX = -I/usr/X11/include -L/usr/X11/lib -lX11 -lXext -lm -g
MLX_FLAGS_MAC = -L$(MLXMACDIR) -lmlx -framework OpenGL -framework AppKit
LIBFT_FLAGS_MAC = -L$(LIBFTDIR) -lfull_libft


SRC= $(addprefix $(SRC_FOLDER), main.c raycasting.c utils.c minimap.c raycast_utils.c hooks.c)

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
	@$(CC) $(CFLAGS) $(SRC) $(LIBFTA) -o $(NAME) $(MLX_FLAGS_MAC) $(LIBFT_FLAGS)
	@mv $(MLXMACDIR)/libmlx.dylib ./ || true

mlx-mac:
	@make -C $(MLXMACDIR)

.PHONY: all clean fclean re libft mlx-linux mac norm