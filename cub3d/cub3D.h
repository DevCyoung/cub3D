#include "mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define PI		3.14159265359
#define RADIN	0.0174533

typedef struct s_vf2d
{
	float	x;
	float	y;
}	t_vf2d;

typedef struct s_vi2d
{
	int	x;
	int	y;
}	t_vi2d;

typedef struct s_image
{
	void	*mlx_img;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	char	*data_addr;
}	t_image;

typedef struct s_object
{
	void	*mlx;
	void	*win;
	t_image *image;
	t_vf2d	direction;
	t_vf2d	position;
}	t_object;

int img_init(void* mlx_ptr, int size_x, int size_y ,t_image *image);
int	img_draw_pixel(t_image *image, int x, int y, int color);
int img_draw_line(t_image *image, t_vi2d start, t_vi2d end, int color);
int img_draw_fill_rectangle(t_image *image, t_vi2d start, t_vi2d len, int color);

t_vf2d casting_vf2d(t_vi2d vi2d);
t_vi2d casting_vi2d(t_vf2d vf2d);
t_vf2d new_vf2d(float x, float y);
t_vi2d new_vi2d(int x, int y);
t_vf2d	new_vf2d_multiple(t_vf2d vf2d, float value);
t_vi2d	new_vi2d_multiple(t_vi2d vi2d, int value);