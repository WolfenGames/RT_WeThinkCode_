/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stere.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 14:04:48 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/16 14:15:25 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	cyan(t_img *stereo, t_img *img)
{
	int		x;
	int		y;
	int		pos;

	y = -1;
	while (y < WIN_H)
	{
		x = -1;
		while (x < WIN_W)
		{
			pos = (x * img->bpp) + (y * img->sl);
			stereo->img[pos] += img->img[pos];
			stereo->img[pos + 1] += img->img[pos + 1];
		}
	}
}

static void	red(t_img *stereo, t_img *img)
{
	int		x;
	int		y;
	int		pos;

	y = -1;
	while (y < WIN_H)
	{
		x = -1;
		while (x < WIN_W)
		{
			pos = (x * img->bpp) + (y * img->sl);
			stereo->img[pos + 2] += img->img[pos + 2];
		}
	}
}

void		gen_stereo(t_env *env)
{
	//set stereo img
	//cyan(&e->cam->stero, &e->cam->img);
	//red(&r->cam->stero, &e->cam->twin->img);
}