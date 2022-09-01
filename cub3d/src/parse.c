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
void	player_pos_init(t_object *info, int x, int y, char dir)
{
	info->pa = 0;
	if (dir == 'S')
		info->pa = PI / 2;
	else if (dir == 'W')
		info->pa = PI;
	else if (dir == 'N')
		info->pa = PI + PI / 2;
	else if (dir == 'E')
		info->pa = 0;
	info->position.x = x + 0.5f;
	info->position.y = y + 0.5f;
}

int	parse(t_object *info, char *path)
{
	FILE *file = fopen(path, "r");
		

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
				player_pos_init(info, i, height, buffa[i]);
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
