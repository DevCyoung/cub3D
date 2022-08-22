#include "cub3D.h"
#include <stdio.h>


#define WINDOW_SIZE_X 500
#define WINDOW_SIZE_Y 500

int main(void)
{
	void	*mlx;
	void	*win;
	t_image image;

	mlx = mlx_init();
	win = mlx_new_window(mlx, WINDOW_SIZE_X, WINDOW_SIZE_Y, "hello world!");

	img_init(mlx, 500, 500, &image);
	t_vi2d s;
	t_vi2d e;

	s.x = 10; s.y = 10;
	e.x = 100; e.y = 100;
	img_draw_line(&image, s, e, 0XFF0000);
	s.x = 102; s.y = 102;
	e.x = 12; e.y = 12;
	img_draw_line(&image, s, e, 0X00FF00);
	s.x = 3; s.y = 100;
	e.x = 400; e.y = 0;
	img_draw_line(&image, s, e, 0X0000FF);
	s.x = 50; s.y = 60;
	e.x = 30; e.y = 500;
	img_draw_line(&image, s, e, 0XFFFF00);
	s.x = 5; s.y = 400;
	e.x = 10; e.y = 175;
	img_draw_line(&image, s, e, 0XFFFFFF);
	s.x = 495; s.y = 5;
	e.x = 5; e.y = 495;
	img_draw_line(&image, s, e, 0XFF00FF);

	t_vi2d len;
	len.x = 490;
	len.y = 490;

	s.x = 0;  s.y = 0;
	img_draw_fill_rectangle(&image, s, len, 0XF0F0F0);
	mlx_put_image_to_window(mlx, win, image.mlx_img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
