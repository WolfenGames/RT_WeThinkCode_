/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 17:11:48 by ibotha            #+#    #+#             */
/*   Updated: 2019/06/17 12:48:24 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** norm = da 0
** o = da 1
*/

void	sphere_surface_col(t_obj *ob, t_ray *c, t_vec point)
{
	t_vec		da[2];
	t_vec		tempvec[3];

	transform(ob->wto, point, da[0]);
	normalize(da[0]);
	FILLVEC(tempvec[0], 0, 1, 0, 0);
	da[1][1] = (find_angle(da[0], tempvec[0]) / M_PI);
	FILLVEC(tempvec[1], da[0][0], 0, da[0][2], 0);
	FILLVEC(tempvec[0], 0, 0, 1, 0);
	da[1][0] = 1 - ((da[0][0] < 0 ? 0 : 2 * M_PI) + (da[0][0] < 0 ? 1 : -1)
		* find_angle(tempvec[0], tempvec[1])) / (2.f * M_PI);
	surface_scale(da[1], ob);
	if (ob->spec_map)
	{
		get_p_img_col(da[1][0], da[1][1], ob->spec_map, c->org);
		FILLVEC(c->org, (c->org[0] / 255.0) * ob->specular_colour[0],
		(c->org[1] / 255.0) * ob->specular_colour[1],
		(c->org[2] / 255.0) * ob->specular_colour[2], 0);
	}
	else
		vec_dup(ob->specular_colour, c->org);
	ob->tex ? get_p_img_col(da[1][0], da[1][1], ob->tex, c->dir) :
		vec_dup(ob->surface_colour, c->dir);
	ob->norm ? get_p_img_col(da[1][0], da[1][1], ob->norm, c->hold)[0] :
		FILLVEC(c->hold, 128, 128, 255, 0);
}

void	sphere_getnorm(t_vec norm, t_vec point, t_obj *obj, t_ray *c)
{
	t_vec		tang;
	t_matrix	m;

	(void)c;
	v_sub(point, obj->org, norm);
	normalize(norm);
	FILLVEC(tang, norm[0], 0, norm[2], 0);
	fill_m_rot_y(m, -90 * M_PI / 180.0);
	transformvec(m, tang, tang);
	normalize(tang);
	norm_offset(norm, tang, c->hold);
}

int		sphere_intersect(t_ray *ray, t_obj *obj)
{
	t_vec	l;
	t_vec	var;
	double	t[2];

	v_sub(ray->org, obj->org, l);
	var[0] = dot(ray->dir, ray->dir);
	var[1] = 2 * dot(ray->dir, l);
	var[2] = dot(l, l) - (obj->radius * obj->radius);
	if (!quad(var, t))
		return (0);
	if (t[0] < 0)
		t[0] = t[1];
	if (t[0] < 0)
		return (0);
	if (t[0] > ray->len)
		return (0);
	ray->len = t[0];
	return (1);
}
