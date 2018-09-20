/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aa.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 16:54:37 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/20 06:58:31 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#define LIM 4

int		di(t_col c1, t_col c2)
{
	t_col dcol;

	v_sub(c1, c2, dcol);
	return (ABS(dcol[0]) > LIM || ABS(dcol[1]) > LIM || ABS(dcol[2]) > LIM);
}

int		checkpoint(t_env *env, t_xy point)
{
	t_col	col[4];

	get_img_col(point[0], point[1], RENDER, col[0]);
	get_img_col(point[0] + 1, point[1], RENDER, col[1]);
	get_img_col(point[0] + 1, point[1] + 1, RENDER, col[2]);
	get_img_col(point[0], point[1] + 1, RENDER, col[3]);

	return (di(col[0], col[1]) || di(col[0], col[2]) || di(col[0], col[3]));
}

double	*cast(t_env *env, t_xy point, t_col ret)
{
	t_ray	ray;
	t_col	c[4];

	generate_ray(&ray, point[0], point[1], env);
	get_col(&ray, env, ret, 0);
	generate_ray(&ray, point[0] + 0.5, point[1], env);
	get_col(&ray, env, c[1], 0);
	generate_ray(&ray, point[0] + 0.5, point[1] + 0.5, env);
	get_col(&ray, env, c[2], 0);
	generate_ray(&ray, point[0], point[1] + 0.5, env);
	get_col(&ray, env, c[3], 0);
	add_col(c[0], c[1], ret);
	add_col(ret, c[2], ret);
	add_col(ret, c[3], ret);
	v_multi(ret, 0.25, ret);
	ret[3] = 255;
	//FILLCOL(ret, 255, 0, 0, 255);
	return (ret);
}

void	aa(t_env *env)
{
	t_xy	point;
	t_col	c;

	point[0] = -1;
	while (++point[0] < RENDER->w)
	{
		point[1] = -1;
		while (++point[1] < RENDER->h)
		{
			if (checkpoint(env, point))
				put_pixel(point[0], point[1], cast(env, point, c), RENDER);
		}
	}
}