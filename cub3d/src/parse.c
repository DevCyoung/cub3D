/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoseo <yoseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 21:12:28 by yoseo             #+#    #+#             */
/*   Updated: 2022/09/01 17:15:01 by yoseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_strlen(char *str)
{
	int	len;

	len = 0;
	if (str == NULL)
		return (0);
	while (str[len])
		++len;
	return (len);
}

int	parse(t_object *info)
{
	FILE *file = fopen("map.cub", "r");
		

	char	buffa[100];
	char	buffb[100];

	ft_bzero(buffa, 100);
	ft_bzero(buffb, 100);
	
	fscanf(file, "%s %s\n", buffa, buffb);
	printf("%s$\n", buffb);
	img_file_init(info->mlx, buffb, &info->no_texture);
	printf("error\n");

	ft_bzero(buffa, 100);
	ft_bzero(buffb, 100);
	fscanf(file, "%s %s\n", buffa, buffb);
	img_file_init(info->mlx, buffb, &info->so_texture);

	ft_bzero(buffa, 100);
	ft_bzero(buffb, 100);
	fscanf(file, "%s %s\n", buffa, buffb);
	img_file_init(info->mlx, buffb, &info->we_texture);

	ft_bzero(buffa, 100);
	ft_bzero(buffb, 100);
	fscanf(file, "%s %s\n", buffa, buffb);
	img_file_init(info->mlx, buffb, &info->ea_texture);

	int 	r,g,b;
	char	type;

	fscanf(file, "%c %d,%d,%d\n", &type, &r, &g, &b);
	if (type == 'F')
		info->fcolor = rgbtod(r, g, b);
	else
		info->ccolor = rgbtod(r, g, b);

	fscanf(file, "%c %d,%d,%d\n", &type, &r, &g, &b);
	if (type == 'F')
		info->fcolor = rgbtod(r, g, b);
	else
		info->ccolor = rgbtod(r, g, b);

	char buffc[10000];
	ft_bzero(buffc, 10000);
	ft_bzero(buffa, 100);
	int width = 0;
	int height = 0;
	
	++height;
	while (1)	
	{
		if (fscanf(file, "%s\n", buffa) != 1)
			break ;
		printf("%s\n", buffa);
		width = ft_strlen(buffa);
		for (int i = 0; i < width; i++)
		{
			if (buffa[i] != '1' && buffa[i] != '0')
			{
				info->pa = 0;
				if (buffa[i] == 'S')
					info->pa = PI / 2;
				else if (buffa[i] == 'W')
					info->pa = PI;
				else if (buffa[i] == 'N')
					info->pa = PI + PI / 2;
				else if (buffa[i] == 'E')
					info->pa = 0;
				
				info->position.x = i + 0.5f;
				info->position.y = height + 0.5f;
				printf("%f %f\n", info->position.x, info->position.y);
				buffc[height * width + i] = '0';	
			}
			else
				buffc[height * width + i] = buffa[i];
		}
		++height;
	}
	info->map_info.height = height;
	info->map_info.width = width;
	info->map_info.map = (char *)malloc(sizeof(char) * height * width);
	for (int i = 0; i < height * width; i++)
		info->map_info.map[i] = buffc[i];
	printf("\n\n\n\n");
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			printf("%c", info->map_info.map[width * i + j]);
		}
		printf("\n");
	}

	
	
	return (0);
}