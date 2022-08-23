/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoseo <yoseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:03:49 by yoseo             #+#    #+#             */
/*   Updated: 2022/08/23 10:13:08 by yoseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int img_draw_pixel(t_image *image, int x, int y, int color)
{
	char	*data_addr;

	if (x < 0 || x >= image->width || y < 0 || y >= image->height)
		return color;
	data_addr = image->data_addr + y * image->size_line + x * (image->bits_per_pixel / 8);
	*(unsigned int  *)data_addr = color;
	return color;
}

int img_get_color(t_image *image, int x, int y)
{
	char	*data_addr;

	if (x < 0 || x >= image->width || y < 0 || y >= image->height)
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
	delta = new_vi2d(end.x - start.x, end.y - start.y);
	if (abs(delta.x) > abs(delta.y))
		step = abs(delta.x);
	else
		step = abs(delta.y);
	inc = new_vf2d(delta.x / (float)step, delta.y / (float)step);
	cur_pos = new_vf2d((float)start.x, (float)start.y);
	while (i < step)
	{
		img_draw_pixel(image, (int)cur_pos.x, (int)cur_pos.y, color);
		cur_pos = new_vf2d(cur_pos.x + inc.x, cur_pos.y + inc.y);
		++i;
	}
	return color;
}

int img_draw_fill_rectangle(t_image *image, t_vi2d start, t_vi2d size, int color)
{
	t_vi2d end_pos;
	int		x;
	int		y;

	y = start.y;
	end_pos = new_vi2d(start.x + size.x, start.y + size.y);
	while (y < end_pos.y)
	{
		x = start.x;
		while (x < end_pos.x)
		{
			img_draw_pixel(image, x, y, color);
			++x;
		}
		++y;
	}
	return color;
}