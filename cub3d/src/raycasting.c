/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoseo <yoseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:13:56 by yoseo             #+#    #+#             */
/*   Updated: 2022/08/26 21:26:01 by yoseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	step_init(t_raycast_hit *hit, t_vf2d start, t_vf2d direct)
{
	float	mx;
	float	my;

	mx = (float)hit->map_check.x;
	my = (float)hit->map_check.y;
	if (direct.x < 0)
	{
		hit->step.x = -1;
		hit->disthv.x = (start.x - mx) * hit->unit_step_size.x;
	}
	else
	{
		hit->step.x = 1;
		hit->disthv.x = ((mx + 1.0f) - start.x) * hit->unit_step_size.x;
	}
	if (direct.y < 0)
	{
		hit->step.y = -1;
		hit->disthv.y = (start.y - my) * hit->unit_step_size.y;
	}
	else
	{
		hit->step.y = 1;
		hit->disthv.y = ((my + 1.0f) - start.y) * hit->unit_step_size.y;
	}
}

static void	raycast_hit_init(t_raycast_hit *hit,
		t_vf2d start, t_vf2d direct)
{
	hit->unit_step_size = new_vf2d(
			sqrtf(1 + (direct.y / direct.x) * (direct.y / direct.x)),
			sqrtf(1 + (direct.x / direct.y) * (direct.x / direct.y)));
	hit->map_check = new_vi2d(((int)start.x), ((int)start.y));
	step_init(hit, start, direct);
	if (hit->disthv.x < hit->disthv.y)
	{
		hit->is_disth = 1;
		hit->distance = hit->disthv.x;
	}
	else
	{
		hit->is_disth = 0;
		hit->distance = hit->disthv.y;
	}
}

static void	raycast_walk(t_raycast_hit *hit, t_map_info *map, float max_dist)
{
	hit->is_hit = 0;
	while (hit->is_hit == 0 && hit->distance < max_dist)
	{
		if (hit->disthv.x < hit->disthv.y)
		{
			hit->map_check.x += hit->step.x;
			hit->distance = hit->disthv.x;
			hit->disthv.x += hit->unit_step_size.x;
			hit->is_disth = 1;
		}
		else
		{
			hit->map_check.y += hit->step.y;
			hit->distance = hit->disthv.y;
			hit->disthv.y += hit->unit_step_size.y;
			hit->is_disth = 0;
		}
		if (hit->map_check.x >= 0 && hit->map_check.x < map->width \
					&& hit->map_check.y >= 0 && hit->map_check.y < map->height)
		{
			if (map->map[hit->map_check.y * map->width + hit->map_check.x] != 0)
				hit->is_hit = 1;
		}
	}
}

static void	wall_dir_init(t_raycast_hit *hit,
		t_vf2d start, t_vf2d direct)
{
	if (hit->is_disth == 1)
	{
		if (direct.x > 0)
			hit->wall_dir = WE;
		else
			hit->wall_dir = EA;
	}
	else
	{
		if (direct.y > 0)
			hit->wall_dir = NO;
		else
			hit->wall_dir = SO;
	}
	hit->hit_point = new_vf2d(start.x + direct.x * hit->distance, \
			start.y + direct.y * hit->distance);
}

t_raycast_hit	raycasting(t_map_info *map,
		t_vf2d start, t_vf2d direct, float max_dist)
{
	t_raycast_hit	hit;

	raycast_hit_init(&hit, start, direct);
	raycast_walk(&hit, map, max_dist);
	wall_dir_init(&hit, start, direct);
	if (hit.distance >= max_dist)
		hit.distance = max_dist;
	return (hit);
}
