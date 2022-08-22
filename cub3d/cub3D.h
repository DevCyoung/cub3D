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

int img_init(void* mlx_ptr, int size_x, int size_y ,t_image *image);
int	img_draw_pixel(t_image *image, int x, int y, int color);
int img_draw_line(t_image *image, t_vi2d start, t_vi2d end, int color);
int img_draw_fill_rectangle(t_image *image, t_vi2d start, t_vi2d len, int color);

