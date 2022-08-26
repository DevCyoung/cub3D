/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoseo <yoseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 06:01:09 by yoseo             #+#    #+#             */
/*   Updated: 2022/08/26 21:27:38 by yoseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

static char	map[256] = 
{
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,
	1,0,1,1,1,1,0,0,0,0,0,0,0,1,0,1,
	1,0,1,1,1,0,1,0,0,0,0,0,1,0,0,1,
	1,0,1,1,0,0,1,0,0,0,0,1,0,0,0,1,
	1,0,1,1,0,0,0,0,0,0,1,0,0,0,0,1,
	1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,
	1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,
	1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,1,1,0,1,0,0,0,0,1,1,1,0,1,
	1,0,0,0,0,1,0,0,0,1,1,1,1,1,0,1,
	1,0,0,1,0,1,0,0,1,1,1,1,1,1,0,1,
	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};

int	init_texture(void *mlx, t_object *player)
{
	img_file_init(mlx, "textures/bluestone.png", &player->no_texture);
	img_file_init(mlx, "textures/redbrick.png", &player->so_texture);
	img_file_init(mlx, "textures/mossy.png", &player->ea_texture);
	img_file_init(mlx, "textures/wood.png", &player->we_texture);
	return (1);
}

int main(void)
{
	void		*mlx;
	void		*win;
	t_image		image;
	t_object	player;

	mlx = mlx_init();
	win = mlx_new_window(mlx, WINDOW_SIZE_X, WINDOW_SIZE_Y, "hello world!");
	ft_bzero(&player, sizeof(player));
	img_init(mlx, WINDOW_SIZE_X, WINDOW_SIZE_Y, &image);
	init_texture(mlx, &player);
	player.position = new_vf2d(1.5f, 1.5f);
	player.image = &image;
	player.mlx = mlx;
	player.win = win;
	player.pa = 0.0f;
	player.map_info.map = &map[0];
	player.map_info.width = 16;
	player.map_info.height = 16;
	mlx_hook(win, X_EVENT_KEY_PRESS, 0, &key_press, &player);
	mlx_hook(win, X_EVENT_KEY_RELEASE, 0, &key_release, &player);
	mlx_loop_hook(mlx, main_loop, &player);
	mlx_loop(mlx);
	free(mlx);
	free(win);
	return (0);
}
