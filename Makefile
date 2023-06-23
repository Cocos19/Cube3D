# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/23 11:15:40 by mprofett          #+#    #+#              #
#    Updated: 2023/06/23 13:59:05 by mprofett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

SRC			= image.c loop.c main.c memory_free.c

SRC_BONUS	=

OBJ			= ${SRC:.c=.o}

OBJ_BONUS	= ${SRC_BONUS:.c=.o}

LIBFT		= libft.a

LIBFT_PATH	= libft

MLX			= libmlx.a

MLX_PATH	= mlx

CC			= gcc

RM			= rm -f

C_FLAGS	= -Wall -Wextra -Werror

MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit

%.o: %.c
	$(CC) $(C_FLAGS) -c $< -o $@

all: ${NAME}

${NAME}: ${OBJ} ${LIBFT} ${MLX}
	${CC} ${OBJ} -o  ${NAME} ${LIBFT} ${MLX_FLAGS} ${MLX}

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
