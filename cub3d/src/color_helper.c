/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoseo <yoseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:20:02 by yoseo             #+#    #+#             */
/*   Updated: 2022/08/24 20:11:36 by yoseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int alphaBlend(int bk, int fr)
{
	int	color;
	int	r;
	int	g;
	int	b;

	color = 0;
	r = ((bk & 0X00FF0000) >> 16) / 3 + ((fr & 0X00FF0000) >> 16) / 3;
	g = ((bk & 0X0000FF00) >> 8) / 3 + ((fr & 0X0000FF00) >> 8) / 3;
	b = ((bk & 0X000000FF)) / 3 + ((fr & 0X000000FF)) / 3;
	color |= r << 16;
	color |= g << 8;
	color |= b;
	return	color;
}

int	img_get_color(t_image *image, int x, int y)
{
	char	*data_addr;

	if (x < 0 || x >= image->width || y < 0 || y >= image->height)
		return (1);
	data_addr = image->data_addr + y * image->size_line
		+ x * (image->bits_per_pixel / 8);
	return (*((int *)data_addr));
}
