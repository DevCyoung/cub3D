/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_world.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoseo <yoseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:33:21 by yoseo             #+#    #+#             */
/*   Updated: 2022/09/01 16:25:04 by yoseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	texture_init(t_raycast_hit hit, t_object *player, t_image *texture)
{
	t_image	*temp;

	temp = NULL;
	if (hit.wall_dir == NO)
		temp = &player->no_texture;
	else if (hit.wall_dir == SO)
		temp = &player->so_texture;
	else if (hit.wall_dir == WE)
		temp = &player->we_texture;
	else if (hit.wall_dir == EA)
		temp = &player->ea_texture;
	if (temp == NULL)
		exit(1);
	texture->bits_per_pixel = temp->bits_per_pixel;
	texture->data_addr = temp->data_addr;
	texture->endian = temp->endian;
	texture->height = temp->height;
	texture->mlx_img = temp->mlx_img;
	texture->size_line = temp->size_line;
	texture->width = temp->width;
}

static void	rendering_box(t_object *player, t_raycast_hit hit, t_vf2d ho, int x)
{
	t_vf2d	tmx;
	float	step;
	t_image	tt;

	texture_init(hit, player, &tt);
	tmx.x = (int)(((hit.hit_point.x) - (int)(hit.hit_point.x)) * tt.width);
	tmx.y = 0;
	step = (float)(tt.width) / ho.x;
	if (hit.is_disth == 1)
	{
		tmx.x = (int)(((hit.hit_point.y) - (int)
					(hit.hit_point.y)) * tt.height);
		step = (float)(tt.height) / ho.x;
	}
	while (ho.y < (int)(ho.x + ho.y))
	{
		if (ho.y >= player->buff_win.height)
			break ;
		img_draw_pixel(&player->buff_win, x, ho.y,
			img_get_color(&tt,
				(int)tmx.x % tt.width, (int)tmx.y % tt.height));
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
				player->position, rad_to_dir(ra), 18);
		ho.x = (WINDOW_SIZE_Y / 1.5f) / (hit.distance * cosf(ra - player->pa));
		ho.y = ((WINDOW_SIZE_Y) / 2) - ho.x / 2;
		img_draw_fill_rectangle(&player->buff_win,
			new_vi2d(i, 0), new_vi2d(1, ho.y), player->ccolor);
		rendering_box(player, hit, ho, i);
		img_draw_fill_rectangle(&player->buff_win,
			new_vi2d(i, ho.x + ho.y),
			new_vi2d(1, WINDOW_SIZE_Y - ho.x + ho.y), player->fcolor);
		ra += RADIN / step;
		++i;
	}
}
