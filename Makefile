# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bdudley <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/10 22:10:26 by bdudley           #+#    #+#              #
#    Updated: 2019/09/15 12:37:13 by bdudley          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

DEBUG = -g

#WFLAGS = -Wall -Wextra -Werror

GFLAGS = -lmlx -framework OpenGL -framework AppKit

MLX = tools_fdf/minilibx_macos

LIBMLX = -L $(MLX) $(GFLAGS)

FDF_SRC = fdf_project/srcs/

SRC = main.c\
      validate.c\
      ft_atoi_hex.c\
      parcing.c\
      array_operations.c
LIBFT = -L libft -lft

OBJ = $(addprefix $(FDF_SRC), $(SRC:%.c=%.o))

HDR = -I fdf_project/includes -I libft/includes

all: $(NAME)

.c.o:
	@gcc -c $(DEBUG) $(WFLAGS) $(HDR) $? -o $@

$(NAME): $(OBJ)
	@make -C libft
	@make -C libft clean
	@make -C $(MLX)
#	@make -C $(MLX) clean
	@gcc $(WFLAGS) -o $(NAME) $(HDR) $(OBJ) $(LIBFT) $(LIBMLX)

clean:
	@rm -f $(OBJ)
	@make -C libft clean
	#@make -C $(MLX) clean

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean
#	@make -C $(MLX) clean

re: fclean all
