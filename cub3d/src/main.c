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

void	win_init(t_object *player)
{
	ft_bzero(player, sizeof(*player));
	player->mlx = mlx_init();
	player->win = mlx_new_window(player->mlx,
			WINDOW_SIZE_X, WINDOW_SIZE_Y, "cub3D");
	img_init(player->mlx, WINDOW_SIZE_X, WINDOW_SIZE_Y, &player->buff_win);
}

int	main(int argc, char **argv)
{
	t_object	player;

	if (argc != 2)
		return (1);
	win_init(&player);
	if (parse(&player, argv[1]) == 1)
	{
		return (1);
	}
	mlx_hook(player.win, X_EVENT_KEY_PRESS, 0, &key_press, &player);
	mlx_hook(player.win, X_EVENT_KEY_RELEASE, 0, &key_release, &player);
	mlx_hook(player.win, X_EVENT_KEY_EXIT, 0, &win_exit, &player);
	mlx_loop_hook(player.mlx, main_loop, &player);
	mlx_loop(player.mlx);
	return (0);
}
