/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoseo <yoseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:13:56 by yoseo             #+#    #+#             */
/*   Updated: 2022/08/23 10:16:29 by yoseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

float	distance(t_vf2d start, t_vf2d end)
{
	float dx;
	float dy;
	float dist;

	dx = end.x - start.x;
	dy = end.y - start.y;
	dist = sqrtf(dx * dx + dy * dy);
	return dist;
}

static	raycasting_init_value(t_vf2d unit_step_size, t_vi2d map_check, t_vf2d ray_len_1d, t_vi2d step)
{
	unit_step_size = new_vf2d(sqrtf(1 + (direct.y / direct.x) * (direct.y / direct.x)),
								sqrtf(1 + (direct.x / direct.y) * (direct.x / direct.y)));
	ray_len_1d = new_vf2d(0,0);
	map_check = new_vi2d(((int)start.x) , ((int)start.y));
	step = 	new_vi2d(0,0);
	
	if (direct.x < 0)
	{
		step.x = -1;
		ray_len_1d.x = (start.x - (float)map_check.x) * unit_step_size.x;
	}
	else
	{
		step.x = 1;
		ray_len_1d.x = (((float)map_check.x + 1) - start.x) * unit_step_size.x;
	}

	if (direct.y < 0)
	{
		step.y = -1;
		ray_len_1d.y = (start.y - (float)map_check.y) * unit_step_size.y;
	}
	else
	{
		step.y = 1;
		ray_len_1d.y = (((float)map_check.y + 1) - start.y) * unit_step_size.y;
	}
}

t_raycast_hit raycasting(t_map_info *map_info, t_vf2d start, t_vf2d direct, float max_dist)
{
	t_raycast_hit	hit;
	t_vf2d			unit_step_size;
	t_vi2d			map_check;
	t_vf2d			ray_len_1d;
	t_vi2d			step;

	
	unit_step_size = new_vf2d(sqrtf(1 + (direct.y / direct.x) * (direct.y / direct.x)),
								sqrtf(1 + (direct.x / direct.y) * (direct.x / direct.y)));
	ray_len_1d = new_vf2d(0,0);
	map_check = new_vi2d(((int)start.x) , ((int)start.y));
	step = 	new_vi2d(0,0);
	
	if (direct.x < 0)
	{
		step.x = -1;
		ray_len_1d.x = (start.x - (float)map_check.x) * unit_step_size.x;
	}
	else
	{
		step.x = 1;
		ray_len_1d.x = (((float)map_check.x + 1) - start.x) * unit_step_size.x;
	}

	if (direct.y < 0)
	{
		step.y = -1;
		ray_len_1d.y = (start.y - (float)map_check.y) * unit_step_size.y;
	}
	else
	{
		step.y = 1;
		ray_len_1d.y = (((float)map_check.y + 1) - start.y) * unit_step_size.y;
	}

	char			is_found;
	float			curdist;
	hit.disth = ray_len_1d.x;
	hit.distv = ray_len_1d.y;

	hit.is_disth = 0;
	is_found = 0;
	curdist = ray_len_1d.x > ray_len_1d.y ? ray_len_1d.y : ray_len_1d.x;
	while (is_found == 0 && curdist < max_dist)
	{
		if (ray_len_1d.x < ray_len_1d.y)
		{
			map_check.x += step.x;
			curdist = ray_len_1d.x;
			hit.disth = ray_len_1d.x;
			ray_len_1d.x += unit_step_size.x;
			hit.is_disth = 1;
		}
		else
		{
			map_check.y += step.y;
			curdist = ray_len_1d.y;
			hit.distv = ray_len_1d.y;
			ray_len_1d.y += unit_step_size.y;
			hit.is_disth = 0;
		}
		if (map_check.x >= 0 && map_check.x < MAP_X && map_check.y >= 0 && map_check.y < MAP_Y)
		{
			if (map_info->map[map_check.y * map_info->size_x + map_check.x] != 0)
				is_found = 1;
		}
	}
	
	hit.distance = curdist;

	if (hit.is_disth == 1)
	{
		if (direct.x < 0)
			hit.wall_dir = NO;
		else
			hit.wall_dir = SO;
	}
	else
	{
		if (direct.y < 0)
			hit.wall_dir = EA;
		else
			hit.wall_dir = WE;
	}

	hit.hit_point = new_vf2d(start.x + direct.x * hit.distance , start.y + direct.y * hit.distance);
	return hit;
}