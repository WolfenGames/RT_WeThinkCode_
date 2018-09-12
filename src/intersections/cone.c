/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 10:07:15 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/12 17:05:21 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void		cone_surface_col(t_obj *ob, t_col c, t_vec point)
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

void		cone_getnorm(t_vec norm, t_vec point, t_obj *obj)
{
	t_vec	lpoint;

	transform(obj->wto, point, lpoint);
	FILLVEC(norm, lpoint[0], lpoint[1], 0, 0);
	normalize(norm);
	norm[2] = (obj->radius / obj->scale[0]);
	normalize(norm);
	transformvec(obj->otw, norm, norm);
}

static int	get_abc(double near, double t[3], t_ray *tr, t_obj *obj)
{
	double	var[3];
	double	c;

	c = pow(obj->radius / obj->scale[0], 2);
	var[0] = tr->dir[0] * tr->dir[0] + tr->dir[1] * tr->dir[1]
				- c * tr->dir[2] * tr->dir[2];
	var[1] = 2 * (tr->org[0] * tr->dir[0] + tr->org[1] * tr->dir[1]
				- c * (tr->org[2] - obj->scale[0] / 2) * tr->dir[2]);
	var[2] = tr->org[0] * tr->org[0] + tr->org[1] * tr->org[1] -
				c * pow((tr->org[2] - obj->scale[0] / 2), 2);
	if (!quad(var, t))
		return (0);
	t[2] = t[0] < 0 ? t[1] : t[0];
	if (t[2] < 0 || t[2] > near)
		return (0);
	return (1);
}

static int	cone_bound(t_obj *obj, double t[3], t_ray *tr)
{
	double	inter;

	inter = tr->dir[2] * t[2] + tr->org[2];
	if (inter < -obj->scale[0] / 2 || inter > obj->scale[0] / 2)
	{
		if (t[2] == t[1])
			return (0);
		t[2] = t[1];
		inter = tr->dir[2] * t[2] + tr->org[2];
		if (inter < -obj->scale[0] / 2 || inter > obj->scale[0] / 2)
			return (0);
	}
	return (1);
}

int			cone_intersect(t_ray *ray, t_obj *obj)
{
	t_ray	tr;
	double	t[3];

	transformvec(obj->wto, ray->dir, tr.dir);
	transform(obj->wto, ray->org, tr.org);
	if (!get_abc(ray->len, t, &tr, obj))
		return (0);
	if (!cone_bound(obj, t, &tr))
		return (0);
	if (ray->len < t[2])
		return (0);
	ray->len = t[2];
	return (1);
}
