# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: angassin <angassin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/23 11:15:40 by mprofett          #+#    #+#              #
#    Updated: 2023/12/01 14:43:24 by angassin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

SRC			= src/image.c src/image_utils.c src/image_screen_raycast_utils.c \
			src/loop.c src/main.c src/parsing/check.c \
			src/parsing/info_parsing.c src/minimap/fov.c src/memory_free.c \
			src/parsing/init_player_infos.c src/minimap/raycasting.c \
			src/minimap/put_pixel.c src/parsing/parse_map.c \
			src/init_data_structures.c src/hooks.c src/moves.c \
			src/moves_rotations.c src/door.c src/sprites.c src/sprites_utils.c \

SRC_BONUS	=

OBJ			= ${SRC:.c=.o}

OBJ_BONUS	= ${SRC_BONUS:.c=.o}

LIBFT		= libft.a

LIBFT_PATH	= libft

MLX			= libmlx.a

MLX_PATH	= mlx

CC			= gcc

RM			= rm -f

C_FLAGS	= -Wall -Wextra -Werror -g3

MLX_FLAGS =  -framework OpenGL -framework AppKit

%.o: %.c
	$(CC) $(C_FLAGS) -c $< -o $@

all: ${NAME}

${NAME}: ${OBJ} ${LIBFT} ${MLX}
	${CC} $(C_FLAGS) ${OBJ} -o  ${NAME} ${LIBFT} ${MLX_FLAGS} ${MLX}

${LIBFT}:
	${MAKE} bonus -C ${LIBFT_PATH}
	mv ${LIBFT_PATH}/${LIBFT} .

${MLX}:
	${MAKE} -C ${MLX_PATH}
	mv ${MLX_PATH}/${MLX} .

bonus: ${OBJ_BONUS} ${LIBFT} ${MLX}
	${CC} ${OBJ_BONUS} -o  ${NAME} ${LIBFT} ${MLX_FLAGS} ${MLX}

clean:
	${MAKE} clean -C ${LIBFT_PATH}
	${MAKE} clean -C ${MLX_PATH}
	${RM} ${OBJ} ${OBJ_BONUS}

fclean: clean
	${RM} ${NAME} ${LIBFT} ${MLX}

re:	fclean all

.PHONY:	all bonus clean fclean re
