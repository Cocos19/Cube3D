# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: angassin <angassin@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/23 11:15:40 by mprofett          #+#    #+#              #
#    Updated: 2023/12/06 16:43:39 by angassin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

SRC			= src/loop.c \
			src/main.c \
			src/memory_free.c \
			src/memory_free_utils.c \
			src/init_data_structures.c \
			src/commands/rotate.c \
			src/parsing/info_parsing.c \
			src/parsing/init_player_infos.c \
			src/parsing/parse_map.c \
			src/rendering/rendering_utils.c \
			src/rendering/screen_raycast_utils.c \
			
SRC_MAND	= src/hooks.c \
			src/parsing/check.c \
			src/rendering/render_screen.c \
			src/commands/move_forward.c \
			src/commands/move_backward.c \
			src/commands/straf_left.c \
			src/commands/straf_right.c \
			src/commands/move_player.c \

SRC_BONUS	= src/hooks_bonus.c \
			src/parsing/check_bonus.c \
			src/commands/door_utils_bonus.c \
			src/commands/door_bonus.c \
			src/minimap/fov_bonus.c \
			src/minimap/raycasting_bonus.c \
			src/minimap/put_pixel_bonus.c \
			src/rendering/render_screen_bonus.c \
			src/rendering/sprites_bonus.c \
			src/rendering/sprites_utils_bonus.c \
			src/commands/move_forward_bonus.c \
			src/commands/move_backward_bonus.c \
			src/commands/straf_left_bonus.c \
			src/commands/straf_right_bonus.c \
			src/commands/move_player_bonus.c \

OBJ			= ${SRC:.c=.o}

OBJ_MAND	= ${SRC_MAND:.c=.o}	

OBJ_BONUS	= ${SRC_BONUS:.c=.o}

LIBFT		= libft.a

LIBFT_PATH	= libft

MLX			= libmlx.a

MLX_PATH	= mlx

CC			= gcc

RM			= rm -f

C_FLAGS	= -Wall -Wextra -Werror -g3

MLX_FLAGS = -framework OpenGL -framework AppKit

%.o: %.c
	$(CC) $(C_FLAGS) -c $< -o $@

all: ${NAME}

${NAME}: ${OBJ} ${OBJ_MAND} ${LIBFT} ${MLX}
	${CC} $(C_FLAGS) ${OBJ} ${OBJ_MAND} -o  ${NAME} ${LIBFT} ${MLX_FLAGS} ${MLX}

${LIBFT}:
	${MAKE} bonus -C ${LIBFT_PATH}
	mv ${LIBFT_PATH}/${LIBFT} .

${MLX}:
	${MAKE} -C ${MLX_PATH}
	mv ${MLX_PATH}/${MLX} .

bonus: ${OBJ} ${OBJ_BONUS} ${LIBFT} ${MLX}
	${CC} $(C_FLAGS) ${OBJ} ${OBJ_BONUS} -o  ${NAME} ${LIBFT} ${MLX_FLAGS} ${MLX}

clean:
	${MAKE} clean -C ${LIBFT_PATH}
	${MAKE} clean -C ${MLX_PATH}
	${RM} ${OBJ} ${OBJ_MAND} ${OBJ_BONUS}

fclean: clean
	${RM} ${NAME} ${LIBFT} ${MLX}

re:	fclean all

.PHONY:	all bonus clean fclean re
