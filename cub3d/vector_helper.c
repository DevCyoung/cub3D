#include "cub3D.h"

t_vf2d casting_vf2d(t_vi2d vi2d)
{
	t_vf2d vf2d;

	vf2d.x = (float)vi2d.x;
	vf2d.y = (float)vi2d.y;
	return (vf2d);
}

t_vi2d casting_vi2d(t_vf2d vf2d)
{

	t_vi2d vi2d;

	vi2d.x = (int)vf2d.x;
	vi2d.y = (int)vf2d.y;
	return (vi2d);
}

t_vf2d	new_vf2d_multiple(t_vf2d vf2d, float value)
{
	vf2d.x *= value;
	vf2d.y *= value;
	return vf2d;
}

t_vi2d	new_vi2d_multiple(t_vi2d vi2d, int value)
{
	vi2d.x *= value;
	vi2d.y *= value;
	return vi2d;
}

t_vf2d new_vf2d(float x, float y)
{
	t_vf2d vf2d;
	
	vf2d.x = x;
	vf2d.y = y;
	return (vf2d);
}

t_vi2d new_vi2d(int x, int y)
{

	t_vi2d vi2d;
	
	vi2d.x = x;
	vi2d.y = y;
	return (vi2d);
}
