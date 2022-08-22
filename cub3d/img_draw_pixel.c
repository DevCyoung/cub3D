#include "cub3D.h"

int img_init(void *mlx_ptr, int size_x, int size_y, t_image *image)
{
	image->mlx_img = mlx_new_image(mlx_ptr, size_x, size_y);
	image->data_addr = mlx_get_data_addr(image->mlx_img, &image->bits_per_pixel, &image->size_line, &image->endian);
	return 1;	
}

int img_draw_pixel(t_image *image, int x, int y, int color)
{
	char	*data_addr;

	data_addr = image->data_addr + y * image->size_line + x * (image->bits_per_pixel / 8);
	*(unsigned int  *)data_addr = color;
	return color;
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
	while (y <= diry)
	{
		x = start.x;
		while (x <= dirx)
		{
			img_draw_pixel(image, x, y, color);
			++x;
		}
		++y;
	}
	return color;
}
