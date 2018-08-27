/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 14:17:23 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/25 15:37:58 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

static void	draw_liney(t_xy a, t_xy b, t_col c, t_img *img)
{
	double	change;
	double	grad;
	double	i;

	change = b[1] - a[1];
	grad = (b[0] - a[0]) / change;
	i = -1;
	while (++i < (ABS(change)))
		put_pixel(a[0] + (DR(i)) * grad, a[1] + (DR(i)), c, img);
}

void		draw_line(t_xy a, t_xy b, t_col c, t_img *img)
{
	double	change;
	double	ychange;
	double	grad;
	double	i;

	change = b[0] - a[0];
	ychange = b[1] - a[1];
	if (ABS(ychange) > (ABS(change)))
		draw_liney(a, b, c, img);
	else
	{
		grad = ychange / change;
		i = -1;
		while (++i < ABS(change))
			put_pixel(a[0] + DR(i), a[1] + DR(i) * grad, c, img);
	}
}

void		put_pixel(int x, int y, t_col c, t_img *img)
{
	int			i;

	if (x < 0 || y < 0 || x > img->w || y > img->h)
		return ;
	i = x * img->bpp + y * img->ll;
	img->dat[i] *= 1 - c[3];
	img->dat[i] += c[2] * 0xff * c[3];
	img->dat[i + 1] *= 1 - c[3];
	img->dat[i + 1] += c[1] * 0xff * c[3];
	img->dat[i + 2] *= 1 - c[3];
	img->dat[i + 2] += c[0] * 0xff * c[3];
}

void		draw_box(t_xy start, t_xy end, t_col c, t_img *img)
{
	int y;
	int x;

	if (start[0] > end[0])
		ft_swap(&start[0], &end[0], sizeof(int));
	if (start[1] > end[1])
		ft_swap(&start[1], &end[1], sizeof(int));
	y = start[1] - 1;
	while (++y < end[1])
	{
		x = start[0] - 1;
		while (++x < end[0])
			put_pixel(x, y, c, img);
	}
}
