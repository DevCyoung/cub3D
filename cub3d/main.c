#include "cub3D.h"
#include <stdio.h>


#define WINDOW_SIZE_X 1024
#define WINDOW_SIZE_Y 1024

#define X_EVENT_KEY_PRESS			2
#define X_EVENT_KEY_RELEASE			3
#define X_EVENT_KEY_EXIT           17

#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_W 13


#define KEY_LEFT 	123
#define KEY_RIGHT	124

#define per_boxsize	128
#define per_player	2
int map[64] = 
{
	1,1,1,1,1,1,1,1,
	1,0,0,0,0,1,0,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,1,0,0,1,
	1,0,0,0,1,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,0,0,1,1,0,1,
	1,1,1,1,1,1,1,1,
};


t_object player;
int	ketmap[4] = {0, 0, 0, 0};

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
	_player = NULL;
	return 1;
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
	_player = NULL;
	return 1;
}

int main_loop(t_object *player)
{
	int y = 0;
	t_vi2d start;
	t_vi2d len;
	t_image *image;

	//draw mini map
	image = player->image;
	while (y < 8)
	{
		int x = 0;
		while (x < 8)
		{
			start.x = x * per_boxsize;
			start.y = y * per_boxsize;

			start.x = start.x ;
			start.y = start.y ;

			len.x = per_boxsize;
			len.y = per_boxsize;
			if (map[y * 8 + x] == 1)
				img_draw_fill_rectangle(image, start, len, 0XFFFFFF);
			else	
				img_draw_fill_rectangle(image, start, len, 0X00FF00);
			++x;

		}
		++y;
	}

	//calc player
	if (ketmap[0])
	{
		player->position.x -= 0.05f;
	}
	else if (ketmap[1])
	{
		player->position.x += 0.05f;
	}

	if (ketmap[2])
	{
		player->position.y -= 0.05f;
	}
	else if(ketmap[3])
	{
		player->position.y += 0.05f;
	}
	// ketmap[0] = 0;
	// ketmap[1] = 0;
	// ketmap[2] = 0;
	// ketmap[3] = 0;
	//draw player
	t_vf2d word_position = new_vf2d_multiple(player->position, per_boxsize);
	t_vi2d player_start = casting_vi2d(word_position);
	t_vi2d player_len = new_vi2d(per_boxsize >> per_player, per_boxsize >> per_player);
	player_start = new_vi2d(player_start.x - player_len.x / 2 , player_start.y - player_len.y / 2);
	img_draw_fill_rectangle(image, player_start, player_len, 0X0FFFF00);
	mlx_put_image_to_window(player->mlx, player->win, image->mlx_img, 0, 0);
	return 1;

}

int main(void)
{
	void	*mlx;
	void	*win;
	t_image image;


	mlx = mlx_init();
	win = mlx_new_window(mlx, WINDOW_SIZE_X, WINDOW_SIZE_Y, "hello world!");
	img_init(mlx, 1024, 1024, &image);
	player.position = new_vf2d(1.5f, 1.5f);
	player.image = &image;
	player.mlx = mlx;
	player.win = win;

	// t_vi2d start;
	// t_vi2d len;
	// while (y < 8)
	// {
	// 	int x = 0;
	// 	while (x < 8)
	// 	{

	// 		start.x = x * per_boxsize;
	// 		start.y = y * per_boxsize;

	// 		start.x = start.x + x + 1;
	// 		start.y = start.y + y + 1;

	// 		len.x = per_boxsize;
	// 		len.y = per_boxsize;
	// 		if (map[y * 8 + x] == 1)
	// 			img_draw_fill_rectangle(&image, start, len, 0XFFFFFF);
	// 		else	
	// 			img_draw_fill_rectangle(&image, start, len, 0X00FF00);
	// 		++x;

	// 	}
	// 	++y;
	// }

	
	// len.x = per_boxsize >> per_player;
	// len.y = per_boxsize >> per_player;

	// player.x *= per_boxsize;
	// player.y *= per_boxsize;
	// start.x = (int)player.x;
	// start.y = (int)player.y;

	// img_draw_fill_rectangle(&image, start, len, 0X0FFFF00);
	mlx_hook(win, X_EVENT_KEY_PRESS, 0, &key_press, &player);
	mlx_hook(win, X_EVENT_KEY_RELEASE, 0, &key_release, &player);

	mlx_loop_hook(mlx, main_loop, &player);
	mlx_loop(mlx);
	return (0);
}
