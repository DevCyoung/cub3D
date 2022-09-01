/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_world.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoseo <yoseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:33:21 by yoseo             #+#    #+#             */
/*   Updated: 2022/09/01 14:36:51 by yoseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_image	*texture_init(t_raycast_hit hit, t_object *player)
{
	t_image	*texture;

	if (hit.wall_dir == NO)
		texture = &player->no_texture;
	else if (hit.wall_dir == SO)
		texture = &player->so_texture;
	else if (hit.wall_dir == WE)
		texture = &player->we_texture;
	else
		texture = &player->ea_texture;
	return (texture);
}

static void	rendering_box(t_object *player, t_raycast_hit hit, t_vf2d ho, int x)
{
	t_vf2d	tmx;
	float	step;
	t_image	*tt;

	tt = texture_init(hit, player);
	tmx.x = (int)(((hit.hit_point.x) - (int)(hit.hit_point.x)) * tt->width);
	tmx.y = 0;
	step = (float)(tt->width) / ho.x;
	if (hit.is_disth == 1)
	{
		tmx.x = (int)(((hit.hit_point.y) - (int)
					(hit.hit_point.y)) * tt->height);
		step = (float)(tt->height) / ho.x;
	}
	while (ho.y < (int)(ho.x + ho.y))
	{
		if (ho.y >= player->buff_win->height)
			break ;
		img_draw_pixel(player->buff_win, x, ho.y,
			img_get_color(tt,
				(int)tmx.x % tt->width, (int)tmx.y % tt->height));
		tmx.y = tmx.y + step;
		++ho.y;
	}
}

void	rendering_word(t_object *player)
{
	t_raycast_hit	hit;
	t_vf2d			ho;
	int				i;
	float			ra;
	float			step;

	i = 0;
	ra = player->pa - (CAMERA_RANGE / 2.0f) * RADIN;
	step = WINDOW_SIZE_X / (float)CAMERA_RANGE;
	while (i < WINDOW_SIZE_X)
	{
		ra = safe_ra(ra);
		hit = raycasting(&player->map_info,
				player->position, rad_to_dir(ra), 15);
		ho.x = (WINDOW_SIZE_Y / 1.5f) / (hit.distance * cosf(ra - player->pa));
		ho.y = ((WINDOW_SIZE_Y) / 2) - ho.x / 2;
		img_draw_fill_rectangle(player->buff_win,
			new_vi2d(i, 0), new_vi2d(1, ho.y), 0X0067E3);
		rendering_box(player, hit, ho, i);
		img_draw_fill_rectangle(player->buff_win,
			new_vi2d(i, ho.x + ho.y),
			new_vi2d(1, WINDOW_SIZE_Y - ho.x + ho.y), 0X808080);
		ra += RADIN / step;
		++i;
	}
}
