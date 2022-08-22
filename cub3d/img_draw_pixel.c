#include "cub3D.h"

int img_init(void *mlx_ptr, int size_x, int size_y, t_image *image)
{
	image->mlx_img = mlx_new_image(mlx_ptr, size_x, size_y);
	image->data_addr = mlx_get_data_addr(image->mlx_img, &image->bits_per_pixel, &image->size_line, &image->endian);
	return 1;	
}

int img_file_init(void *mlx_ptr, char *file_name, t_image *image)
{
	image->mlx_img = mlx_png_file_to_image(mlx_ptr, file_name, &image->width, &image->height);
	image->data_addr = mlx_get_data_addr(image->mlx_img, &image->bits_per_pixel, &image->size_line, &image->endian);
	return 1;
}

int img_draw_pixel(t_image *image, int x, int y, int color)
{
	char	*data_addr;

	if (x < 0 || x >= WINDOW_SIZE_X || y < 0 || y >= WINDOW_SIZE_Y)
		return color;
	data_addr = image->data_addr + y * image->size_line + x * (image->bits_per_pixel / 8);
	*(unsigned int  *)data_addr = color;
	return color;
}

int img_get_color(t_image *image, int x, int y)
{
	char	*data_addr;

	if (x < 0 || x >= 2048 || y < 0 || y >= 2048)
		return 1;
	data_addr = image->data_addr + y * image->size_line + x * (image->bits_per_pixel / 8);
	return *((unsigned int  *)data_addr);
}

int img_draw_line(t_image *image, t_vi2d start, t_vi2d end, int color)
{
	t_vi2d	delta;
	t_vf2d	cur_pos;
	t_vf2d	inc;
	int		step;
	int		i;

	i = 0;
	delta.x = end.x - start.x;
	delta.y = end.y - start.y;
	if (abs(delta.x) > abs(delta.y))
		step = abs(delta.x);
	else
		step = abs(delta.y);
	inc.x = delta.x / (float)step;
	inc.y = delta.y / (float)step;
	cur_pos.x = (float)start.x;
	cur_pos.y = (float)start.y;
	while (i <= step)
	{
		img_draw_pixel(image, (int)cur_pos.x, (int)cur_pos.y, color);
		cur_pos.x += inc.x;
		cur_pos.y += inc.y;
		++i;
	}
	return color;
}

int img_draw_fill_rectangle(t_image *image, t_vi2d start, t_vi2d len, int color)
{
	int	x;
	int	y;
	int dirx;
	int diry;

	dirx = start.x + len.x;
	diry = start.y + len.y;
	y = start.y;
	while (y < diry)
	{
		x = start.x;
		while (x < dirx)
		{
			img_draw_pixel(image, x, y, color);
			++x;
		}
		++y;
	}
	return color;
}

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