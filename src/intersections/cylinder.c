/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 14:32:18 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/12 15:58:10 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void			cylinder_surface_col(t_obj *ob, t_col c, t_vec point)
{
	t_vec		norm;
	t_vec		tempvec[3];
	t_vec		o;
	t_img		*img;

	img = ob->tex;
	transform(ob->wto, point, tempvec[2]);
	cylinder_getnorm(norm, tempvec[2], ob);
	if (!img)
	{
		FILLCOL(c, ob->surface_colour[0], ob->surface_colour[1],
			ob->surface_colour[2], ob->surface_colour[3]);
		return ;
	}
	FILLVEC(tempvec[0], 0, 1, 0, 0);
	o[1] = (find_angle(norm, tempvec[0]) / M_PI);
	FILLVEC(tempvec[1], norm[0], 0, norm[2], 0);
	FILLVEC(tempvec[0], 0, 0, 1, 0);
	o[0] = 1 - ((norm[0] < 0 ? 0 : 2 * M_PI) + (norm[0] < 0 ? 1 : -1)
		* find_angle(tempvec[0], tempvec[1])) / (2.f * M_PI);
	o[0] = (o[0] * ob->tex_scale[0] - (int)(o[0] * ob->tex_scale[0])) * img->w;
	o[1] = (o[1] * ob->tex_scale[1] - (int)(o[1] * ob->tex_scale[1])) * img->h;
	get_img_col(o[0], o[1], img, c);
}

static int		c_bound(t_vec temp, t_obj *obj, double t[3], t_ray tr)
{
	double	c;

	if (temp[2] < -obj->scale[0] / 2 || temp[2] > obj->scale[0] / 2)
	{
		if (t[2] == t[1])
			return (0);
		t[2] = t[1];
		v_multi(tr.dir, t[2], temp);
		v_add(tr.org, temp, temp);
		c = atan2(temp[1], temp[0]);
		if (c < 0.0f)
			c += 2.0f * M_PI;
		if (temp[2] < -obj->scale[0] / 2 || temp[2] > obj->scale[0] / 2)
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

static int		get_abc(double near, double t[3], t_ray *tr, t_obj *obj)
{
	double	var[3];

	var[0] = tr->dir[0] * tr->dir[0] + tr->dir[1] * tr->dir[1];
	var[1] = 2 * (tr->org[0] * tr->dir[0] + tr->org[1] * tr->dir[1]);
	var[2] = tr->org[0] * tr->org[0] + tr->org[1] * tr->org[1] -
				pow(obj->radius, 2);
	if (!quad(var, t))
		return (0);
	t[2] = t[0] < 0 ? t[1] : t[0];
	if (t[2] < 0 || t[2] > near)
		return (0);
	return (1);
}

int				cylinder_intersect(t_ray *ray, t_obj *obj)
{
	t_vec	temp;
	t_ray	tr;
	double	c;
	double	t[3];

	transformvec(obj->wto, ray->dir, tr.dir);
	transform(obj->wto, ray->org, tr.org);
	if (!get_abc(ray->len, t, &tr, obj))
		return (0);
	v_multi(tr.dir, t[2], temp);
	v_add(tr.org, temp, temp);
	c = atan2f(temp[1], temp[0]);
	if (c < 0.0f)
		c += 2.0f * M_PI;
	if (!c_bound(temp, obj, t, tr))
		return (0);
	if (ray->len < t[2])
		return (0);
	ray->len = t[2];
	return (1);
}
