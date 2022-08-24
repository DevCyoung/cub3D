#include "mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define PI		3.14159265359
#define RADIN	0.0174533

#define WINDOW_SIZE_X 600
#define WINDOW_SIZE_Y 600
#define	CAMERA_RANGE				60
#define MINIMAP_SIZE				3
#define MINIMAP_BOX_SIZE			8


#define X_EVENT_KEY_PRESS			2
#define X_EVENT_KEY_RELEASE			3
#define X_EVENT_KEY_EXIT            17
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

#define R_MASK	0X00FF0000
#define G_MASK	0X0000FF00
#define B_MASK	0X000000FF


typedef	struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

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

typedef struct s_map_info
{
	int		width;
	int		height;
	char	*map;
} 	t_map_info;

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
	t_map_info map_info;
	float	pa;
	t_image *image;
	t_image we_texture;
	t_image ea_texture;
	t_image no_texture;
	t_image so_texture;
	t_vf2d	direction;
	t_vf2d	position;
	int	keymap[4];
	int	keyarrow[2];
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
	t_vf2d		unit_step_size;
	t_vi2d		map_check;
	t_vi2d		step;
	t_vf2d		disthv;
	char		is_disth;
	char		is_hit;
	float		distance;
	t_wall_dir	wall_dir;
	t_vf2d		hit_point;
}	t_raycast_hit;

/*
img_draw 
*/
int img_init(void* mlx_ptr, int size_x, int size_y ,t_image *image);
int img_file_init(void *mlx_ptr, char *file_name, t_image *image);

/*
img_draw
*/
int	img_draw_pixel(t_image *image, int x, int y, int color);
int img_draw_line(t_image *image, t_vi2d start, t_vi2d end, int color);
int img_draw_fill_rectangle(t_image *image, t_vi2d start, t_vi2d len, int color);
int img_get_color(t_image *image, int x, int y);

/*
vector_helper
*/
t_vf2d casting_vf2d(t_vi2d vi2d);
t_vi2d casting_vi2d(t_vf2d vf2d);
t_vf2d new_vf2d(float x, float y);
t_vi2d new_vi2d(int x, int y);
t_vf2d	new_vf2d_multi(t_vf2d vf2d, float value);
t_vi2d	new_vi2d_multi(t_vi2d vi2d, int value);
t_vf2d	rad_to_dir(float radin);
t_vf2d vf2d_add(t_vf2d a, t_vf2d b);
t_vf2d	vf2d_multi(t_vf2d vf2d, float mul);

/*
raycasting
*/
t_raycast_hit raycasting(t_map_info *map_info, t_vf2d start, t_vf2d direct, float max_dist);

/*
keyevent
*/
int	key_press(int keycode, t_object *player);
int	key_release(int keycode, t_object *_player);


int main_loop(t_object *player);

/*
colorhelper
*/
int alphaBlend(int bk, int fr);
int	img_get_color(t_image *image, int x, int y);


/*
math_helper
*/
float	safe_ra(float ra);
void	ft_bzero(void *s, size_t n);
float	distance(t_vf2d start, t_vf2d end);

/*
rendering
*/
void	rendering_word(t_object *player);