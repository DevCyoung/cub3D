/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoseo <yoseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 20:02:04 by yoseo             #+#    #+#             */
/*   Updated: 2022/08/24 20:18:32 by yoseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ns;

	ns = (unsigned char *)s;
	if (n == 0)
		return ;
	while (n > 0)
	{
		--n;
		ns[n] = 0;
	}
}

float	safe_ra(float ra)
{
	if (ra < 0)
		ra += 2 * PI;
	else if (ra > 2 * PI)
		ra -= 2 * PI;
	return (ra);
}

float	distance(t_vf2d start, t_vf2d end)
{
	float	dx;
	float	dy;
	float	dist;

	dx = end.x - start.x;
	dy = end.y - start.y;
	dist = sqrtf(dx * dx + dy * dy);
	return (dist);
}