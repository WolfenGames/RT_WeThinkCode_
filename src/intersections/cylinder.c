/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 14:32:18 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/12 18:35:42 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void			cylinder_surface_col(t_obj *ob, t_col c, t_vec point)
{
	t_vec		lpoint;
	t_vec		temp;
	t_vec		o;
	t_img		*img;

	img = ob->tex;
	transform(ob->wto, point, lpoint);
	if (!img)
	{
		FILLCOL(c, ob->surface_colour[0], ob->surface_colour[1],
			ob->surface_colour[2], ob->surface_colour[3]);
		return ;
	}
	o[1] = 1 - (lpoint[2] + ob->scale[0] / 2.0) / ob->scale[0];
	lpoint[2] = 0;
	normalize(lpoint);
	FILLVEC(temp, 0, (lpoint[0] < 0 ? 1 : -1), 0, 0);
	o[0] = 1 - (((lpoint[0] < 0 ? 0 : M_PI) + find_angle(temp, lpoint)) / (2 * M_PI));
	o[0] = (o[0] * ob->tex_scale[0] - (int)(o[0] * ob->tex_scale[0])) * img->w;
	o[1] = (o[1] * ob->tex_scale[1] - (int)(o[1] * ob->tex_scale[1])) * img->h;
	get_img_col(o[0], o[1], img, c);
}

static int		c_bound(t_obj *obj, double t[3], t_ray *tr)
{
	double	inter;
	double	inter2;

	inter = tr->dir[2] * t[0] + tr->org[2];
	inter2 = tr->dir[2] * t[1] + tr->org[2];
	if (inter < -obj->scale[0] / 2 || inter > obj->scale[0] / 2)
	{
		if (inter2 < -obj->scale[0] / 2 || inter2 > obj->scale[0] / 2)
			return (0);
	}
	return (1);
}

void			cylinder_getnorm(t_vec norm, t_vec point, t_obj *obj)
{
	t_vec	lpoint;

	transform(obj->wto, point, lpoint);
	FILLVEC(norm, lpoint[0], lpoint[1], 0, 0);
	normalize(norm);
	transformvec(obj->otw, norm, norm);
}

static int		get_abc(double t[3], t_ray *tr, t_obj *obj)
{
	double	var[3];

	var[0] = tr->dir[0] * tr->dir[0] + tr->dir[1] * tr->dir[1];
	var[1] = 2 * (tr->org[0] * tr->dir[0] + tr->org[1] * tr->dir[1]);
	var[2] = tr->org[0] * tr->org[0] + tr->org[1] * tr->org[1] -
				pow(obj->radius, 2);
	if (!quad(var, t))
		return (0);
	t[2] = t[0] < 0 ? t[1] : t[0];
	if (t[2] < 0 || t[2] > tr->len)
		return (0);
	return (1);
}

int				cylinder_intersect(t_ray *ray, t_obj *obj)
{
	t_ray	tr;
	double	t[3];

	transformvec(obj->wto, ray->dir, tr.dir);
	transform(obj->wto, ray->org, tr.org);
	tr.len = ray->len;
	if (!get_abc(t, &tr, obj))
		return (0);
	if (!c_bound(obj, t, &tr))
		return (0);
	if (ray->len < t[2])
		return (0);
	ray->len = t[2];
	return (1);
}
