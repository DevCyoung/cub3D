/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoseo <yoseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:01:28 by yoseo             #+#    #+#             */
/*   Updated: 2022/08/24 20:11:37 by yoseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	img_init(void *mlx_ptr, int width, int height, t_image *image)
{
	image->mlx_img = mlx_new_image(mlx_ptr, width, height);
	image->data_addr = mlx_get_data_addr(image->mlx_img,
			&image->bits_per_pixel, &image->size_line, &image->endian);
	image->width = width;
	image->height = height;
	return (1);
}

int	img_file_init(void *mlx_ptr, char *file_name, t_image *image)
{
	image->mlx_img = mlx_png_file_to_image(mlx_ptr,
			file_name, &image->width, &image->height);
	image->data_addr = mlx_get_data_addr(image->mlx_img,
			&image->bits_per_pixel, &image->size_line, &image->endian);
	return (1);
}
