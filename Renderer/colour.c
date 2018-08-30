/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 13:10:26 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/30 13:45:36 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

double	*sc_col(t_col c, double s, t_col ret)
{
	BLU(ret) = BLU(c) * s;
	GRN(ret) = GRN(c) * s;
	RED(ret) = RED(c) * s;
	ALP(ret) = ALP(c) * s;
	if (BLU(ret) > 255)
		return (sc_col(ret, (255 / BLU(ret)), ret));
	if (GRN(ret) > 255)
		return (sc_col(ret, (255 / GRN(ret)), ret));
	if (RED(ret) > 255)
		return (sc_col(ret, (255 / RED(ret)), ret));
	return (ret);
}

double	*add_col(t_col a, t_col b, t_col ret)
{
	BLU(ret) = ft_clamp(255, 0, BLU(a) + BLU(b));
	GRN(ret) = ft_clamp(255, 0, GRN(a) + GRN(b));
	RED(ret) = ft_clamp(255, 0, RED(a) + RED(b));
	ALP(ret) = ft_clamp(255, 0, ALP(a) + ALP(b));
	return (ret);
}

double	*get_img_col(int x, int y, t_img *img, t_col ret)
{
	unsigned int	*dat;
	unsigned int	tmp;

	dat = (unsigned int*)img->dat;
	if (x >= 0 && x < img->w && y >= 0 && y < img->h)
		tmp = dat[x + (int)(y * img->w)];
	else
		tmp = 0;
	RED(ret) = (tmp & 0xff);
	tmp /= 0x100;
	GRN(ret) = (tmp & 0xff);
	tmp /= 0x100;
	BLU(ret) = (tmp & 0xff);
	tmp /= 0x100;
	ALP(ret) = (tmp & 0xff);
	return (ret);
}
