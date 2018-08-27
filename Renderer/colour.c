/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 13:10:26 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/25 15:02:25 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

float	*sc_col(t_col c, double s, t_col ret)
{
	BLU(ret) = BLU(c) * s;
	GRN(ret) = GRN(c) * s;
	RED(ret) = RED(c) * s;
	ALP(ret) = ALP(c) * s;
	if (BLU(ret) > 1.0)
		return (sc_col(ret, (1.0 / BLU(c)), ret));
	if (GRN(ret) > 255)
		return (sc_col(ret, (1.0 / GRN(c)), ret));
	if (RED(ret) > 1.0)
		return (sc_col(ret, (1.0 / RED(c)), ret));
	return (ret);
}

float	*add_col(t_col a, t_col b, t_col ret)
{
	BLU(ret) = BLU(a) + BLU(b);
	GRN(ret) = GRN(a) + GRN(b);
	RED(ret) = RED(a) + GRN(b);
	ALP(ret) = ALP(a) + ALP(b);
	return (ret);
}

float	*get_img_col(int x, int y, t_img *img, t_col ret)
{
	unsigned int	*dat;
	unsigned int	tmp;

	dat = (unsigned int*)img->dat;
	if (x >= 0 && x < img->w && y >= 0 && y < img->h)
		tmp = dat[x + (int)(y * img->w)];
	else
		tmp = 0;
	RED(ret) = (tmp & 0xff) / 255.0;
	tmp /= 0x100;
	GRN(ret) = (tmp & 0xff) / 255.0;
	tmp /= 0x100;
	BLU(ret) = (tmp & 0xff) / 255.0;
	tmp /= 0x100;
	ALP(ret) = (tmp & 0xff) / 255.0;
	return (ret);
}
