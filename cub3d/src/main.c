/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoseo <yoseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 06:01:09 by yoseo             #+#    #+#             */
/*   Updated: 2022/09/01 17:18:38 by yoseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static char	map[256] = 
// {
// 	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
// 	1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,
// 	1,0,1,1,1,1,0,0,0,0,0,0,0,1,0,1,
// 	1,0,1,1,1,0,1,0,0,0,0,0,1,0,0,1,
// 	1,0,1,1,0,0,1,0,0,0,0,1,0,0,0,1,
// 	1,0,1,1,0,0,0,0,0,0,1,0,0,0,0,1,
// 	1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,
// 	1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,
// 	1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,
// 	1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,
// 	1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,
// 	1,0,0,1,1,0,1,0,0,0,0,1,1,1,0,1,
// 	1,0,0,0,0,1,0,0,0,1,1,1,1,1,0,1,
// 	1,0,0,1,0,1,0,0,1,1,1,1,1,1,0,1,
// 	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,
// 	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
// };

// int	init_texture(void *mlx, t_object *player)
// {
// 	img_file_init(mlx, "textures/bluestone.png", &player->no_texture);
// 	img_file_init(mlx, "textures/redbrick.png", &player->so_texture);
// 	img_file_init(mlx, "textures/mossy.png", &player->ea_texture);
// 	img_file_init(mlx, "textures/wood.png", &player->we_texture);
// 	return (1);
// }

int main(void)
{
	void		*mlx;
	void		*win;
	t_object	player;

	mlx = mlx_init();
	win = mlx_new_window(mlx, WINDOW_SIZE_X, WINDOW_SIZE_Y, "hello world!");
	ft_bzero(&player, sizeof(player));
	img_init(mlx, WINDOW_SIZE_X, WINDOW_SIZE_Y, &player.buff_win);
	player.mlx = mlx;
	player.win = win;
	player.pa = 0.0f;
	parse(&player);
	mlx_hook(win, X_EVENT_KEY_PRESS, 0, &key_press, &player);
	mlx_hook(win, X_EVENT_KEY_RELEASE, 0, &key_release, &player);
	mlx_hook(win, X_EVENT_KEY_EXIT, 0, &win_exit, &player);
	mlx_loop_hook(mlx, main_loop, &player);
	mlx_loop(mlx);
	free(mlx);
	free(win);
	return (0);
}
