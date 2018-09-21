/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oldschool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 06:37:27 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/21 11:23:19 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	color_set(t_col c, float diff, t_col ret)
{
	ret[0] += c[0] * diff / 16.0;
	ret[1] += c[1] * diff / 16.0;
	ret[2] += c[2] * diff / 16.0;
}

void	do_da_colour(t_env *env, int x, int y, t_col ret[2])
{
	float	factor;
	t_col	err;

	factor = 4.0;
	ret[1][0] = (factor * ret[0][0] * 255.0) / (factor * 255.0);
	ret[1][1] = (factor * ret[0][1] * 255.0) / (factor * 255.0);
	ret[1][2] = (factor * ret[0][2] * 255.0) / (factor * 255.0);
	err[0] = ret[0][0] - ret[1][0];
	err[1] = ret[0][1] - ret[1][1];
	err[2] = ret[0][2] - ret[1][2];
	color_set(err, 7, err);
	put_pixel(x + 1, y, err, RENDER);
	color_set(err, 3, err);
	put_pixel(x - 1, y + 1, err, RENDER);
	color_set(err, 5, err);
	put_pixel(x, y + 1, err, RENDER);
	color_set(err, 1, err);
	put_pixel(x + 1, y + 1, err, RENDER);
}

void	floid_dithering(t_env *env)
{
	int		i;
	int		j;
	t_col	ret[2];
	t_img	*old;

	i = 0;
	old = RENDER;
	RENDER = ((t_env*)env)->img[5];
	while (++i < WIN_W - 1)
	{
		j = -1;
		while (++j < WIN_H - 1)
		{
			get_img_col(i, j, old, ret[0]);
			do_da_colour(env, i, j, ret);
		}
	}
}
