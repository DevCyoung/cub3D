/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_minimap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoseo <yoseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:47:27 by yoseo             #+#    #+#             */
/*   Updated: 2022/09/01 14:36:51 by yoseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	map_color(t_object *player, t_vi2d pixel)
{
	t_map_info	map_info;
	int			color;

	map_info = player->map_info;
	if (pixel.x < 0 || pixel.x >= MAP_X || pixel.y < 0 || pixel.y >= MAP_Y)
		color = 0X0080808F;
	else if (map_info.map[pixel.y * map_info.width + pixel.x] == 0)
		color = 0X00000000;
	else
		color = 0X00FFFFFF;
	return (color);
}

static void	rendering_player(t_object *player)
{
	t_image	*image;
	t_vi2d	start;
	t_vi2d	len;
	int		p_size;

	image = player->buff_win;
	p_size = (float)(WINDOW_SIZE_X / MINIMAP_SIZE) / 20;
	start = new_vi2d(((WINDOW_SIZE_X / MINIMAP_SIZE) / 2) - p_size / 2,
			((WINDOW_SIZE_Y / MINIMAP_SIZE) / 2) - p_size / 2);
	len = new_vi2d(p_size, p_size);
	img_draw_fill_rectangle(image, start, len, 0X00FFFF00);
}

void	rendering_minimap(t_object *player)
{
	t_vi2d	idx;
	t_vf2d	map_step;
	t_vf2d	offset;

	idx = new_vi2d(0, 0);
	map_step.x = MINIMAP_BOX_SIZE / (float)(WINDOW_SIZE_X / MINIMAP_SIZE);
	map_step.y = MINIMAP_BOX_SIZE / (float)(WINDOW_SIZE_Y / MINIMAP_SIZE);
	offset = new_vf2d(player->position.x - 4.0f, player->position.y - 4.0f);
	while (idx.y < WINDOW_SIZE_Y / MINIMAP_SIZE)
	{
		offset.x = player->position.x - 4.0f;
		idx.x = 0;
		while (idx.x < WINDOW_SIZE_X / MINIMAP_SIZE)
		{
			img_draw_pixel(player->buff_win, idx.x, idx.y,
				alpha_blend(map_color(player,
						new_vi2d((int)offset.x, (int)offset.y)),
					img_get_color(player->buff_win, idx.x, idx.y)));
			offset.x += map_step.x;
			++idx.x;
		}
		offset.y += map_step.y;
		++idx.y;
	}
	rendering_player(player);
}
