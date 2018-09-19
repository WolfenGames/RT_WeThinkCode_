/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 14:50:41 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/19 11:49:46 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	plane_surface_col(t_obj *ob, t_col c, t_vec point)
{
	t_vec		tempvec[3];
	t_vec		o;
	t_img		*img;

	img = ob->tex;
	transform(ob->wto, point, tempvec[2]);
	tempvec[2][0] += ob->scale[0] / 2.0;
	tempvec[2][1] += ob->scale[1] / 2.0;
	if (!img)
	{
		FILLCOL(c, ob->surface_colour[0], ob->surface_colour[1],
				ob->surface_colour[2], ob->surface_colour[3]);
		return ;
	}
	o[0] = tempvec[2][0] / ob->scale[0];
	o[1] = 1 - tempvec[2][1] / ob->scale[1];
	o[0] = (o[0] * ob->tex_scale[0] - (int)(o[0] * ob->tex_scale[0])) * img->w;
	o[1] = (o[1] * ob->tex_scale[1] - (int)(o[1] * ob->tex_scale[1])) * img->h;
	get_img_col(o[0], o[1], img, c);
}

void	plane_getnorm(t_vec norm, t_vec point, t_obj *obj)
{
	t_vec	lpoint;

	FILLVEC(norm, 0, 0, 1, 0);
	transform(obj->wto, point, lpoint);
	transformvec(obj->otw, norm, norm);
}

int		plane_intersect(t_ray *ray, t_obj *obj)
{
	t_ray	tr;
	double	t[2];

	transformvec(obj->wto, ray->dir, tr.dir);
	transform(obj->wto, ray->org, tr.org);
	normalize(tr.dir);
	if (!tr.dir[2])
		return (0);
	t[0] = tr.org[2] / -tr.dir[2];
	if (t[0] < 0)
		return (0);
	if (ray->len < t[0])
		return (0);
	t[1] = t[0] * tr.dir[1] + tr.org[1];
	if (t[1] > obj->scale[1] / 2.0 || t[1] < -obj->scale[1] / 2.0)
		return (0);
	t[1] = t[0] * tr.dir[0] + tr.org[0];
	if (t[1] > obj->scale[0] / 2.0 || t[1] < -obj->scale[0] / 2.0)
		return (0);
	ray->len = t[0];
	return (1);
}
