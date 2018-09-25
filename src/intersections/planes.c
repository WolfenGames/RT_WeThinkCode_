/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 14:50:41 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/24 17:06:09 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	plane_surface_col(t_obj *ob, t_ray *c, t_vec point)
{
	t_vec		tempvec[3];
	t_vec		o;

	transform(ob->wto, point, tempvec[2]);
	tempvec[2][0] += ob->scale[0] / 2.0;
	tempvec[2][1] += ob->scale[1] / 2.0;
	o[0] = tempvec[2][0] / ob->scale[0];
	o[1] = 1 - tempvec[2][1] / ob->scale[1];
	surface_scale(o, ob);
	ob->spec_map ? (get_p_img_col(o[0], o[1], ob->spec_map, c->org), FILLVEC(c->org,
		(c->org[0] / 255.0) * ob->specular_colour[0],
		(c->org[1] / 255.0) * ob->specular_colour[1],
		(c->org[2] / 255.0) * ob->specular_colour[2], 0)) : 
		vec_dup(ob->specular_colour, c->org);
	ob->tex ? get_p_img_col(o[0], o[1], ob->tex, c->dir) :
		vec_dup(ob->surface_colour, c->dir);
	ob->norm ? get_p_img_col(o[0], o[1], ob->norm, c->hold)[0] :
		FILLVEC(c->hold, 128, 128, 255, 0);
}

void	plane_getnorm(t_vec norm, t_vec point, t_obj *obj, t_col map)
{
	t_vec	lpoint;
	t_vec	tang;
	(void)map;

	FILLVEC(norm, 0, 0, 1, 0);
	FILLVEC(tang, 1, 0, 0, 0);
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
