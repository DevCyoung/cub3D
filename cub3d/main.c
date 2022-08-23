/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoseo <yoseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 06:01:09 by yoseo             #+#    #+#             */
/*   Updated: 2022/08/23 10:18:12 by yoseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

char map[256] = 
{
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,
	1,0,1,1,1,1,0,0,0,0,0,0,0,1,0,1,
	1,0,1,1,1,0,1,0,0,0,0,0,1,0,0,1,
	1,0,1,1,0,0,1,0,0,0,0,1,0,0,0,1,
	1,0,1,1,0,0,0,0,0,0,1,0,0,0,0,1,
	1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,
	1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,
	1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,1,1,0,1,0,0,0,0,1,1,1,0,1,
	1,0,0,0,0,1,0,0,0,1,1,1,1,1,0,1,
	1,0,0,1,0,1,0,0,1,1,1,1,1,1,0,1,
	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};

int	ketmap[4] = {0, 0, 0, 0};
int	keyarrow[2] = {0,0};

unsigned int AlphaBlend(const unsigned int bg, const unsigned int src)
{
   unsigned int a = src >> 24;    /* alpha */

   /* If source pixel is transparent, just return the background */
   if (0 == a) 
      return bg;

   /* alpha blending the source and background colors */
   unsigned int rb = (((src & 0x00ff00ff) * a) +  
      ((bg & 0x00ff00ff) * (0xff - a))) & 0xff00ff00;
   unsigned int    g  = (((src & 0x0000ff00) * a) + 
      ((bg & 0x0000ff00) * (0xff - a))) & 0x00ff0000;

    return (src & 0xff000000) | ((rb | g) >> 8);
}

int	key_press(int keycode, t_object *_player)
{
	if (keycode == KEY_A)
		ketmap[0] = 1;
	else if (keycode == KEY_D)
		ketmap[1] = 1;
	if (keycode == KEY_W)
		ketmap[2] = 1;
	else if (keycode == KEY_S)
		ketmap[3] = 1;

	if (keycode == KEY_LEFT)
		keyarrow[0] = 1;
	if (keycode == KEY_RIGHT)
		keyarrow[1] = 1;

	return _player->pa;
}

int	key_release(int keycode, t_object *_player)
{
	if (keycode == KEY_A)
		ketmap[0] = 0;
	if (keycode == KEY_D)
		ketmap[1] = 0;
	if (keycode == KEY_W)
		ketmap[2] = 0;
	if (keycode == KEY_S)
		ketmap[3] = 0;

	if (keycode == KEY_LEFT)
		keyarrow[0] = 0;
	if (keycode == KEY_RIGHT)
		keyarrow[1] = 0;
	
	return _player->pa;
}

int main_loop(t_object *player)
{
	
	t_vi2d start;
	t_vi2d len;
	t_image *image;

	//draw mini map version1
	t_map_info map_info;
	map_info.map = &map[0];
	map_info.size_x = MAP_X;
	map_info.size_y = MAP_Y;
	image = player->image;
	
	if (ketmap[0])
	{
		t_vf2d dir = new_vf2d(-cosf(player->pa + PI / 2), -sinf(player->pa + PI / 2));
		t_raycast_hit h = raycasting(&map_info, player->position, dir, 0.5f);
		if (h.distance > 0.5f)
		{
			player->position.x -= cosf(player->pa + PI / 2) * 0.05f;
			player->position.y -= sinf(player->pa + PI / 2) * 0.05f;
		}
			

	}
	else if (ketmap[1])
	{
		t_vf2d dir = new_vf2d(cosf(player->pa + PI / 2), sinf(player->pa + PI / 2));
		t_raycast_hit h = raycasting(&map_info, player->position, dir, 0.5f);
		if (h.distance > 0.5f)
		{
			player->position.x += cosf(player->pa + PI / 2) * 0.05f;
			player->position.y += sinf(player->pa + PI / 2) * 0.05f;
		}
	}

	if (ketmap[2])
	{
		t_vf2d dir = new_vf2d(cosf(player->pa), sinf(player->pa));
		t_raycast_hit h = raycasting(&map_info, player->position, dir, 0.5f);
		if (h.distance > 0.5f)
		{
			player->position.x += cosf(player->pa) * 0.05f;
			player->position.y += sinf(player->pa) * 0.05f;
		}
	}
	else if(ketmap[3])
	{
		t_vf2d dir = new_vf2d(-cosf(player->pa), -sinf(player->pa));
		t_raycast_hit h = raycasting(&map_info, player->position, dir, 0.5f);
		if (h.distance > 0.5f)
		{
			player->position.x -= cosf(player->pa) * 0.05f;
			player->position.y -= sinf(player->pa) * 0.05f;
		}
	}

	if (keyarrow[0])
		player->pa -= RADIN * 2.9f;
	if (keyarrow[1])
		player->pa += RADIN * 2.9f;
	if (player->pa < 0)
		player->pa += 2 * PI;
	if (player->pa > 2 * PI)
		player->pa -= 2 * PI;

	//draw ray
	float ra = player->pa - (CAMERA_RANGE / 2.0f) * RADIN;
	//int raycount = 60 * 2;
	int i = 0;
	float ssss = WINDOW_SIZE_X / (float)CAMERA_RANGE;
	
	while (i < WINDOW_SIZE_X)
	{
		

		if (ra < 0)
		{
			ra += 2 * PI;
		}
		else if (ra > 2 * PI)
		{
			ra -= 2 * PI;
		}

		t_vf2d dirction = new_vf2d(cosf(ra), sinf(ra));


		t_raycast_hit hit = raycasting(&map_info, player->position, dirction, 15);
		t_vi2d line_s = casting_vi2d(new_vf2d_multiple(player->position, per_boxsize));
		t_vi2d line_e;
		line_e.x = hit.distance * per_boxsize * dirction.x + line_s.x;
		line_e.y = hit.distance * per_boxsize * dirction.y + line_s.y;
		//player ray
		//img_draw_line(image, line_s, line_e, 0XFF0000);
		float pa = ra - player->pa;
		if (pa < 0)
		{
			pa += 2 * PI;
		}
		else if (pa > 2 * PI)
		{
			pa -= 2 * PI;
		}

		
		float lineh = (WINDOW_SIZE_Y / 1.5f) / (hit.distance * cosf(pa));

		if (lineh >= 2024.0f)
		{
			lineh = 2024.0f;
		}

        float lineo = ((WINDOW_SIZE_Y) / 2) - lineh / 2;		

		//sky
		start = new_vi2d(i, 0);
		len	= new_vi2d(1, lineo);
		img_draw_fill_rectangle(image, start, len, 0X0067E3);

		//box
		
		float tm = 0.0f;
		float tx = 0.0f;

		t_image *tt;
		
		if (hit.wall_dir == NO)
		{
			tt = &player->no_texture;
		}
		else if (hit.wall_dir == SO)
		{
			tt = &player->so_texture;
		}
		else if (hit.wall_dir == WE)
		{
			tt = &player->we_texture;
		}
		else if (hit.wall_dir == EA)
		{
			tt = &player->ea_texture;
		}

		float sstep;
		if (hit.is_disth == 1)
		{
			tm = (int)(((hit.hit_point.y) - (int)(hit.hit_point.y)) * tt->height);
			sstep = (float)(tt->height) / lineh;
		}
		else
		{
			tm = (int)(((hit.hit_point.x) - (int)(hit.hit_point.x)) * tt->width);
			sstep = (float)(tt->width) / lineh;
		}

		

		for (int j = lineo; j < (int)(lineh + lineo); j++)
		{
			int co = img_get_color(tt, (int)tm % tt->width, (int)tx % tt->height);
			img_draw_pixel(image, i, j, co);
			tx = tx + sstep;
		}



		//img_draw_fill_rectangle(image, start, len, 0XFFFFFF);



		//floor
		start = new_vi2d(i, lineo + lineh);
		len	= new_vi2d(1, WINDOW_SIZE_Y - lineo + lineh);
		img_draw_fill_rectangle(image, start, len, 0X808080);

		ra += RADIN / ssss;
		++i;
	}
	int y = 0;
	float map_step_x =  MINIMAP_BOX_SIZE / (float)(WINDOW_SIZE_X / MINIMAP_SIZE);
	float map_step_y =  MINIMAP_BOX_SIZE / (float)(WINDOW_SIZE_Y / MINIMAP_SIZE);
	t_vf2d offset = new_vf2d(player->position.x - 4.0f, player->position.y - 4.0f);
	printf("%f , %f\n", offset.x, offset.y);
	
	y = 0;
	while (y < WINDOW_SIZE_Y / MINIMAP_SIZE)
	{
		int x = 0;
		offset.x = player->position.x - 4.0f;
		while (x < WINDOW_SIZE_X / MINIMAP_SIZE)
		{
			t_vi2d ip = new_vi2d((int)offset.x, (int)offset.y);
			int color = 0;
			if (ip.x < 0 || ip.x >= MAP_X || ip.y < 0 || ip.y >= MAP_Y)
			{
				color = 0X0080808F;
			}
			else if (map[ip.y * MAP_X + ip.x] == 0)
			{
				color = 0X00000000;
			}
			else
			{
				color = 0X00FFFFFF;
			}
			img_draw_pixel(image, x, y, AlphaBlend(color, img_get_color(image, x, y)));
			offset.x += map_step_x;
			++x;
		}
		offset.y += map_step_y;
		++y;
	}
	int p_size = (float)(WINDOW_SIZE_X / MINIMAP_SIZE) / 20;
	start = new_vi2d(((WINDOW_SIZE_X / MINIMAP_SIZE) / 2) - p_size / 2, ((WINDOW_SIZE_Y / MINIMAP_SIZE) / 2) - p_size / 2);
	len	  = new_vi2d(p_size, p_size);
	img_draw_fill_rectangle(image, start, len, 0X00FFFF00);
	mlx_put_image_to_window(player->mlx, player->win, image->mlx_img, 0, 0);
	return 1;

}

int main(void)
{
	void	*mlx;
	void	*win;
	t_image image;
	t_object player;
	
	mlx = mlx_init();
	win = mlx_new_window(mlx, WINDOW_SIZE_X, WINDOW_SIZE_Y, "hello world!");

	img_init(mlx, WINDOW_SIZE_X, WINDOW_SIZE_Y, &image);

	//init_texture
	img_file_init(mlx, "pics/mossy.png", &player.ea_texture);
	img_file_init(mlx, "pics/bluestone.png", &player.no_texture);
	img_file_init(mlx, "pics/redbrick.png", &player.so_texture);
	img_file_init(mlx, "pics/wood.png", &player.we_texture);

	player.position = new_vf2d(1.5f, 1.5f);
	player.image = &image;
	player.mlx = mlx;
	player.win = win;
	player.pa = 0.0f;
	
	mlx_hook(win, X_EVENT_KEY_PRESS, 0, &key_press, &player);
	mlx_hook(win, X_EVENT_KEY_RELEASE, 0, &key_release, &player);
	mlx_loop_hook(mlx, main_loop, &player);
	mlx_loop(mlx);
	return (0);
}
