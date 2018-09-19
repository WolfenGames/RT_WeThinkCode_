/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stereo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 14:04:48 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/19 17:50:16 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	cyan(t_img *stereo, t_img *img, t_env *env)
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
			if (stereo->id != IFINAL->id)
				printf("WOOOPS");
			pos = (x * img->bpp) + (y * img->ll);
			stereo->dat[pos] = img->dat[pos];
			stereo->dat[pos + 1] = img->dat[pos + 1];
		}
	}
}

void	red(t_img *stereo, t_img *img, t_env *env)
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
			if (stereo->id != IFINAL->id)
				printf("WOOOPS");
			pos = (x * img->bpp) + (y * img->ll);
			stereo->dat[pos + 2] = img->dat[pos + 2];
		}
	}
}

void		gen_stereo(t_env *env)
{
	RENDER = env->img[4];
	cyan(RENDER, ILEFT, env);
	red(RENDER, IRIGHT, env);
	env->stereod = 1;
}
