# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    MakeFile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoseo <yoseo@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/09 10:55:55 by yoseo             #+#    #+#              #
#    Updated: 2022/05/13 09:50:26 by yoseo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./minilibx/
LFLAGS = -L./minilibx/ -lmlx -framework OpenGL -framework AppKit -lz

MLX = ./minilibx/libmlx.a

SRCS = main.c\
	   img_draw_pixel.c\

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) $(MLX)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) -o $(NAME)

$(MLX) :
	@make -C minilibx

%.o : %.c
	$(CC) $(CFLAGS) -c $^

clean :
	make -C minilibx clean
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean
	make all

.PHONY : all clean fclean re 
