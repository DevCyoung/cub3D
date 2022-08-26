/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoseo <yoseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:10:55 by yoseo             #+#    #+#             */
/*   Updated: 2022/08/26 19:18:46 by yoseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_move(t_object *player, float dx, float dy)
{
	t_raycast_hit	hit3;
	t_vf2d			move_dir;

	move_dir = new_vf2d(dx, dy);
	hit3 = raycasting(&player->map_info, player->position, move_dir, 0.3f);
	if (hit3.is_hit == 0)
		player->position = vf2d_add(
				vf2d_multi(move_dir, 0.05f), player->position);
	else
	{
		if (hit3.is_disth == 0)
			player->position.x += move_dir.x * 0.05f;
		else
			player->position.y += move_dir.y * 0.05f;
	}
}

void	key_calc(t_object *player)
{
	t_map_info	*map_info;
	t_vf2d		move_dir;

	map_info = &player->map_info;
	move_dir = new_vf2d(0, 0);
	if (player->keymap[0])
		player_move(player,
			-cosf(player->pa + PI / 2), -sinf(player->pa + PI / 2));
	else if (player->keymap[1])
		player_move(player,
			cosf(player->pa + PI / 2), sinf(player->pa + PI / 2));
	if (player->keymap[2])
		player_move(player,
			cosf(player->pa), sinf(player->pa));
	else if (player->keymap[3])
		player_move(player,
			-cosf(player->pa), -sinf(player->pa));
	if (player->keyarrow[0])
		player->pa -= RADIN * 2.9f;
	else if (player->keyarrow[1])
		player->pa += RADIN * 2.9f;
	player->pa = safe_ra(player->pa);
}

int	main_loop(t_object *player)
{
	key_calc(player);
	rendering_word(player);
	rendering_minimap(player);
	mlx_put_image_to_window(player->mlx,
		player->win, player->image->mlx_img, 0, 0);
	return (1);
}
