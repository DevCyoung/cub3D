/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoseo <yoseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:11:12 by yoseo             #+#    #+#             */
/*   Updated: 2022/09/01 17:21:03 by yoseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	win_exit(t_object *player)
{
	mlx_destroy_image(player->mlx, player->buff_win.mlx_img);
	mlx_destroy_image(player->mlx, player->we_texture.mlx_img);
	mlx_destroy_image(player->mlx, player->ea_texture.mlx_img);
	mlx_destroy_image(player->mlx, player->no_texture.mlx_img);
	mlx_destroy_image(player->mlx, player->so_texture.mlx_img);
	mlx_destroy_window(player->mlx, player->win);
	exit(0);
	return (0);
}

int	key_press(int keycode, t_object *player)
{
	if (keycode == KEY_A)
		player->keymap[0] = 1;
	else if (keycode == KEY_D)
		player->keymap[1] = 1;
	if (keycode == KEY_W)
		player->keymap[2] = 1;
	else if (keycode == KEY_S)
		player->keymap[3] = 1;
	if (keycode == KEY_LEFT)
		player->keyarrow[0] = 1;
	if (keycode == KEY_RIGHT)
		player->keyarrow[1] = 1;
	if (keycode == KEY_ESC)
		win_exit(player);
	return (0);
}

int	key_release(int keycode, t_object *player)
{
	if (keycode == KEY_A)
		player->keymap[0] = 0;
	if (keycode == KEY_D)
		player->keymap[1] = 0;
	if (keycode == KEY_W)
		player->keymap[2] = 0;
	if (keycode == KEY_S)
		player->keymap[3] = 0;
	if (keycode == KEY_LEFT)
		player->keyarrow[0] = 0;
	if (keycode == KEY_RIGHT)
		player->keyarrow[1] = 0;
	return (0);
}
