/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 14:32:18 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/25 11:18:39 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			cylinder_surface_col(t_obj *ob, t_ray *c, t_vec point)
{
	t_vec		lpoint;
	t_vec		temp;
	t_vec		o;

	transform(ob->wto, point, lpoint);
	o[1] = 1 - (lpoint[2] + ob->scale[0] / 2.0) / ob->scale[0];
	o[2] = lpoint[2];
	lpoint[2] = 0;
	FILLVEC(temp, 0, (lpoint[0] < 0 ? 1 : -1), 0, 0);
	o[0] = 1 - (((lpoint[0] < 0 ? 0 : M_PI)
		+ find_angle(temp, lpoint)) / (2 * M_PI));
	if (ABS(o[2]) > ((ob->scale[0] / 2.0) * 0.99999))
		cap_col(o, lpoint, ob);
	surface_scale(o, ob);
	if (ob->spec_map)
 	{
		get_p_img_col(o[0], o[1], ob->spec_map, c->org);
		FILLVEC(c->org,
		(c->org[0] / 255.0) * ob->specular_colour[0],
		(c->org[1] / 255.0) * ob->specular_colour[1],
		(c->org[2] / 255.0) * ob->specular_colour[2], 0);
	 }
	 else 
		vec_dup(ob->specular_colour, c->org);
	ob->tex ? get_p_img_col(o[0], o[1], ob->tex, c->dir) :
		vec_dup(ob->surface_colour, c->dir);
}

static void		c_bound(t_obj *obj, double t[3], t_ray *tr)
{
	double	inter;
	double	inter2;
	double	xy[2];

	inter = tr->dir[2] * t[0] + tr->org[2];
	inter2 = tr->dir[2] * t[1] + tr->org[2];
	if (inter < -obj->scale[0] / 2 || inter > obj->scale[0] / 2)
		t[0] = -1;
	if (inter2 < -obj->scale[0] / 2 || inter2 > obj->scale[0] / 2)
		t[1] = -1;
	xy[0] = t[2] * tr->dir[0] + tr->org[0];
	xy[1] = t[2] * tr->dir[1] + tr->org[1];
	if ((xy[0] * xy[0] + xy[1] * xy[1]) > (obj->radius * obj->radius))
		t[2] = -1;
	xy[0] = t[3] * tr->dir[0] + tr->org[0];
	xy[1] = t[3] * tr->dir[1] + tr->org[1];
	if ((xy[0] * xy[0] + xy[1] * xy[1]) > (obj->radius * obj->radius))
		t[3] = -1;
	if (t[0] < 0)
		t[0] = t[1];
	t[1] = t[2] < 0 ? t[3] : t[2];
	if (t[1] < t[0])
		ft_swap(&t[0], &t[1], sizeof(double));
}

void			cylinder_getnorm(t_vec norm, t_vec point, t_obj *obj)
{
	t_vec	lpoint;

	transform(obj->wto, point, lpoint);
	FILLVEC(norm, lpoint[0], lpoint[1], 0, 0);
	if (ABS(lpoint[2]) > ((obj->scale[0] / 2.0) * 0.99999))
		FILLVEC(norm, 0, 0, lpoint[2] < 0 ? -1 : 1, 0);
	normalize(norm);
	transformvec(obj->otw, norm, norm);
}

static int		get_abc(double t[3], t_ray *tr, t_obj *obj)
{
	double	var[3];

	if (!tr->dir[2])
		t[2] = -1;
	else
		t[2] = (obj->scale[0] / 2.0 - tr->org[2]) / tr->dir[2];
	if (!tr->dir[2])
		t[3] = -1;
	else
		t[3] = (-obj->scale[0] / 2.0 - tr->org[2]) / tr->dir[2];
	if (t[3] < t[2])
		ft_swap(&t[2], &t[3], sizeof(double));
	var[0] = tr->dir[0] * tr->dir[0] + tr->dir[1] * tr->dir[1];
	var[1] = 2 * (tr->org[0] * tr->dir[0] + tr->org[1] * tr->dir[1]);
	var[2] = tr->org[0] * tr->org[0] + tr->org[1] * tr->org[1] -
				pow(obj->radius, 2);
	if (!quad(var, t))
		return (0);
	return (1);
}

int				cylinder_intersect(t_ray *ray, t_obj *obj)
{
	t_ray	tr;
	double	t[4];

	transformvec(obj->wto, ray->dir, tr.dir);
	transform(obj->wto, ray->org, tr.org);
	tr.len = ray->len;
	if (!get_abc(t, &tr, obj))
	{
		t[0] = -1;
		t[1] = -1;
	}
	c_bound(obj, t, &tr);
	if (t[0] < 0)
		t[0] = t[1];
	if (t[0] < 0 || t[0] > ray->len)
		return (0);
	ray->len = t[0];
	return (1);
}
