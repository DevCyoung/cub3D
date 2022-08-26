/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoseo <yoseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:10:55 by yoseo             #+#    #+#             */
/*   Updated: 2022/08/24 22:40:24 by yoseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_move(t_object *player, float dx, float dy)
{
	t_raycast_hit	hit3;
	// t_raycast_hit	hit2;
	// t_raycast_hit	hit3;
	t_vf2d			move_dir;

	move_dir = new_vf2d(dx, dy);
	// hit1 = raycasting(&player->map_info, player->position, move_dir, 0.3f);
	// move_dir = new_vf2d(dx - cosf(20), dy - sinf(20));
	// hit2 = raycasting(&player->map_info, player->position, move_dir, 0.3f);
	// move_dir = new_vf2d(dx + cosf(20), dy + sinf(20));
	hit3 = raycasting(&player->map_info, player->position, move_dir, 0.3f);
	//move_dir = new_vf2d(dx, dy);
	//if (hit1.is_hit == 0 && hit2.is_hit == 0 && hit3.is_hit == 0)
	if (hit3.is_hit == 0)
		player->position = vf2d_add(vf2d_multi(move_dir, 0.05f), player->position);
	else
	{
		if (hit3.is_disth == 0)
			player->position.x += dx * 0.05f;
		else
			player->position.y += dy * 0.05f;
	}

}

void	key_calc(t_object *player)
{
	t_map_info *map_info;
	t_vf2d	move_dir;

	map_info = &player->map_info;
	move_dir = new_vf2d(0, 0);
	if (player->keymap[0])
		player_move(player, -cosf(player->pa + PI / 2), -sinf(player->pa + PI / 2));
	else if (player->keymap[1])
		player_move(player, cosf(player->pa + PI / 2), sinf(player->pa + PI / 2));
	if (player->keymap[2])
		player_move(player, cosf(player->pa), sinf(player->pa));
	else if(player->keymap[3])
		player_move(player, -cosf(player->pa), -sinf(player->pa));
	if (player->keyarrow[0])
		player->pa -= RADIN * 2.9f;
	else if (player->keyarrow[1])
		player->pa += RADIN * 2.9f;
	player->pa = safe_ra(player->pa);
}



void	rendering_minimap(t_object *player)
{
	t_image *image;
	t_map_info map_info;
	
	map_info = player->map_info;
	image = player->image;

	int y = 0;
	float map_step_x =  MINIMAP_BOX_SIZE / (float)(WINDOW_SIZE_X / MINIMAP_SIZE);
	float map_step_y =  MINIMAP_BOX_SIZE / (float)(WINDOW_SIZE_Y / MINIMAP_SIZE);
	t_vf2d offset = new_vf2d(player->position.x - 4.0f, player->position.y - 4.0f);
	
	y = 0;
	while (y < WINDOW_SIZE_Y / MINIMAP_SIZE)
	{
		int x = 0;
		offset.x = player->position.x - 4.0f;
		while (x < WINDOW_SIZE_X / MINIMAP_SIZE)
		{
			t_vi2d ip = new_vi2d((int)offset.x, (int)offset.y);
			int color = 0;
			if (ip.x < 0 || ip.x >= MAP_X || ip.y < 0 || ip.y >= MAP_Y)
				color = 0X0080808F;
			else if (map_info.map[ip.y * map_info.width + ip.x] == 0)
				color = 0X00000000;
			else
				color = 0X00FFFFFF;
			img_draw_pixel(image, x, y, alpha_blend(color, img_get_color(image, x, y)));
			offset.x += map_step_x;
			++x;
		}
		offset.y += map_step_y;
		++y;
	}
	//player
	int p_size = (float)(WINDOW_SIZE_X / MINIMAP_SIZE) / 20;
	t_vi2d start = new_vi2d(((WINDOW_SIZE_X / MINIMAP_SIZE) / 2) - p_size / 2, ((WINDOW_SIZE_Y / MINIMAP_SIZE) / 2) - p_size / 2);
	t_vi2d len	 = new_vi2d(p_size, p_size);
	img_draw_fill_rectangle(image, start, len, 0X00FFFF00);
}

int main_loop(t_object *player)
{
	t_image *image;
	t_map_info map_info;

	//draw mini map version1
	map_info = player->map_info;
	image = player->image;
	key_calc(player);
	rendering_word(player);
	rendering_minimap(player);
	mlx_put_image_to_window(player->mlx, player->win, image->mlx_img, 0, 0);
	return 1;

}
