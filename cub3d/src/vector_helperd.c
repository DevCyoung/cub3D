/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_helperd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoseo <yoseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:37:06 by yoseo             #+#    #+#             */
/*   Updated: 2022/08/26 18:37:10 by yoseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vf2d	new_vf2d(float x, float y)
{
	t_vf2d	vf2d;

	vf2d.x = x;
	vf2d.y = y;
	return (vf2d);
}

t_vi2d	new_vi2d(int x, int y)
{
	t_vi2d	vi2d;

	vi2d.x = x;
	vi2d.y = y;
	return (vi2d);
}

t_vf2d	rad_to_dir(float radin)
{
	t_vf2d	vf2d;

	vf2d.x = cosf(radin);
	vf2d.y = sinf(radin);
	return (vf2d);
}

t_vf2d	vf2d_multi(t_vf2d vf2d, float mul)
{
	return (new_vf2d(vf2d.x * mul, vf2d.y * mul));
}

t_vf2d	vf2d_add(t_vf2d a, t_vf2d b)
{
	return (new_vf2d(a.x + b.x, a.y + b.y));
}
