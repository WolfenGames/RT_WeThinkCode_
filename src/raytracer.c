/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 17:12:38 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/25 17:12:39 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

static void	generate_ray(t_ray *ray, t_xy coord, t_env *env)
{
	const double	invheight = 1 / WIN_H;
	const double	invwidth = 1 / WIN_W;
	const double	angle = tan(90.0 * 0.5 * M_PI / 180.0);

	(void)env;
	ray->org[0] = 0;
	ray->org[1] = 0;
	ray->org[2] = 20;
	ray->dir[0] = (2 * (coord[0] + 0.5) * invwidth - 1) * WIN_W
		* invheight * angle;
	ray->dir[1] = (1 - 2 * (coord[1] + 0.5) * invheight) * angle;
	ray->dir[2] = -1;
	normalize(ray->dir);
}

void	*raytracer(void *env)
{
	t_xy		coord;
	t_col		c;
	t_ray		ray;
	const t_img	*img = find_img(&((t_env*)env)->ren, ((t_env*)env)->img[2]);

	coord[1] = -1;
	((t_env*)env)->progress = 0.0f;
	FILLCOL(c, 0.0, 0.0, 0.0, 1.0);
	while (++coord[1] < WIN_H)
	{
		coord[0] = -1;
		while (++coord[0] < WIN_W)
		{
			generate_ray(&ray, coord, env);
			get_col(&ray, env);
			put_pixel(coord[0], coord[1], c, (t_img*)img);
			((t_env*)env)->progress = (coord[0] + coord[1] * WIN_W)
				/ (WIN_H * WIN_W);
		}
    }
	return (0);
}
