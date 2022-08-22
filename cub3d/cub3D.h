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
	float	pa;
	t_image *image;
	t_vf2d	direction;
	t_vf2d	position;
}	t_object;

typedef enum e_wall_dir
{
	WE = 0,
	EA,
	NO,
	SO,
}	t_wall_dir;

typedef struct s_raycast_hit
{
	char		is_hit;
	float		distance;
	t_vf2d		hit_point;
	t_vi2d		map_position;
	t_wall_dir	wall_dir;
	float		disth;
	float		distv;
}	t_raycast_hit;

typedef struct s_map_info
{
	int		size_x;
	int		size_y;
	char	*map;
} 	t_map_info;


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

t_raycast_hit raycasting(t_map_info *map_info, t_vf2d start, t_vf2d direct, float max_dist);

float	distance(t_vf2d start, t_vf2d end);