/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 13:10:26 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/20 11:09:40 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

double	*sc_col(t_col c, double s, t_col ret)
{
	BLU(ret) = BLU(c) * s;
	GRN(ret) = GRN(c) * s;
	RED(ret) = RED(c) * s;
	ALP(ret) = ALP(c) * s;
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
	BLU(ret) = (tmp & 0xff);
	tmp /= 0x100;
	GRN(ret) = (tmp & 0xff);
	tmp /= 0x100;
	RED(ret) = (tmp & 0xff);
	tmp /= 0x100;
	ALP(ret) = (tmp & 0xff);
	return (ret);
}

double	*mask_col(t_col base, t_col mask, t_col ret)
{
	ret[0] = ft_min(mask[0], base[0]);
	ret[1] = ft_min(mask[1], base[1]);
	ret[2] = ft_min(mask[2], base[2]);
	ret[3] = ft_min(mask[3], base[3]);
	return (ret);
}
