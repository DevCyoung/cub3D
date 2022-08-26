# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoseo <yoseo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/09 10:55:55 by yoseo             #+#    #+#              #
#    Updated: 2022/08/26 19:18:06 by yoseo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./minilibx/
LFLAGS = -L./minilibx/ -lmlx -framework OpenGL -framework AppKit -lz

MLX = ./minilibx/libmlx.a

SRCDIR = src/

SRC  = main.c\
	   img_draw.c\
	   img_init.c\
	   raycasting.c\
	   key_event.c\
	   main_loop.c\
	   color_helper.c\
	   rendering_world.c\
	   rendering_minimap.c\
	   math_helper.c\
	   vector_helperd.c\

SRCS = $(addprefix $(SRCDIR), $(SRC))

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) $(MLX)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) -o $(NAME)

$(MLX) :
	@make -C minilibx

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@ -I./include

clean :
	make -C minilibx clean
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean
	make all

.PHONY : all clean fclean re 
