#include "mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define PI		3.14159265359
#define RADIN	0.0174533

#define WINDOW_SIZE_X 2048
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

#define MAP_X		16
#define MAP_Y		16
#define per_boxsize	64
#define per_player	2

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
	int		width;
	int		height;
	char	*data_addr;
}	t_image;


typedef struct s_object
{
	void	*mlx;
	void	*win;
	float	pa;
	t_image *image;
	t_image we_texture;
	t_image ea_texture;
	t_image no_texture;
	t_image so_texture;
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
	char		is_disth;
}	t_raycast_hit;

typedef struct s_map_info
{
	int		size_x;
	int		size_y;
	char	*map;
} 	t_map_info;


int img_init(void* mlx_ptr, int size_x, int size_y ,t_image *image);
int img_file_init(void *mlx_ptr, char *file_name, t_image *image);

int	img_draw_pixel(t_image *image, int x, int y, int color);
int img_draw_line(t_image *image, t_vi2d start, t_vi2d end, int color);
int img_draw_fill_rectangle(t_image *image, t_vi2d start, t_vi2d len, int color);

t_vf2d casting_vf2d(t_vi2d vi2d);
t_vi2d casting_vi2d(t_vf2d vf2d);
t_vf2d new_vf2d(float x, float y);
t_vi2d new_vi2d(int x, int y);
t_vf2d	new_vf2d_multiple(t_vf2d vf2d, float value);
t_vi2d	new_vi2d_multiple(t_vi2d vi2d, int value);
int img_get_color(t_image *image, int x, int y);

t_raycast_hit raycasting(t_map_info *map_info, t_vf2d start, t_vf2d direct, float max_dist);

float	distance(t_vf2d start, t_vf2d end);