/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoseo <yoseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:03:49 by yoseo             #+#    #+#             */
/*   Updated: 2022/08/24 14:55:35 by yoseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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