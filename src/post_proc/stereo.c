/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stereo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 14:04:48 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/21 11:23:28 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	cyan(t_img *stereo, t_img *img)
{
	int		x;
	int		y;
	int		pos;

	y = -1;
	while (y++ < WIN_H)
	{
		x = -1;
		while (x++ < WIN_W)
		{
			pos = (x * img->bpp) + (y * img->ll);
			stereo->dat[pos] = img->dat[pos];
			stereo->dat[pos + 1] = img->dat[pos + 1];
		}
	}
}

void	red(t_img *stereo, t_img *img)
{
	int		x;
	int		y;
	int		pos;

	y = -1;
	while (y++ < WIN_H)
	{
		x = -1;
		while (x++ < WIN_W)
		{
			pos = (x * img->bpp) + (y * img->ll);
			stereo->dat[pos + 2] = img->dat[pos + 2];
		}
	}
}

void	gen_stereo(t_env *env)
{
	RENDER = env->img[4];
	cyan(RENDER, ILEFT);
	red(RENDER, IRIGHT);
	env->stereod = 1;
}
