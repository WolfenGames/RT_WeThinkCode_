/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 10:07:15 by ibotha            #+#    #+#             */
/*   Updated: 2019/06/17 12:29:34 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** data 0 is lp
** data 1 is temp
** data 2 is o coord
*/

void		cone_surface_col(t_obj *ob, t_ray *c, t_vec point)
{
	t_vec		data[3];

	transform(ob->wto, point, data[0]);
	data[2][1] = 1 - (data[0][2] + ob->scale[0] / 2.0) / ob->scale[0];
	data[2][2] = data[0][2];
	data[0][2] = 0;
	FILLVEC(data[1], 0, (data[0][0] < 0 ? 1 : -1), 0, 0);
	data[2][0] = 1 - (((data[0][0] < 0 ? 0 : M_PI) +
		find_angle(data[1], data[0])) / (2 * M_PI));
	if (ABS(data[2][2]) > ((ob->scale[0] / 2.0) * 0.99999))
		cap_col(data[2], data[0], ob);
	surface_scale(data[2], ob);
	if (ob->spec_map)
	{
		get_p_img_col(data[2][0], data[2][1], ob->spec_map, c->org);
		FILLVEC(c->org, (c->org[0] / 255.0) * ob->specular_colour[0],
		(c->org[1] / 255.0) * ob->specular_colour[1],
		(c->org[2] / 255.0) * ob->specular_colour[2], 0);
	}
	else
		vec_dup(ob->specular_colour, c->org);
	ob->tex ? get_p_img_col(data[2][0], data[2][1], ob->tex, c->dir) :
		vec_dup(ob->surface_colour, c->dir);
	ob->norm ? get_p_img_col(data[2][0], data[2][1], ob->norm, c->hold)[0] :
		FILLVEC(c->hold, 128, 128, 255, 0);
}

void		cone_getnorm(t_vec norm, t_vec point, t_obj *obj, t_ray *c)
{
	t_vec		lpoint;
	t_vec		tang;
	t_matrix	m;

	transform(obj->wto, point, lpoint);
	FILLVEC(norm, lpoint[0], lpoint[1], 0, 0);
	(void)c;
	fill_m_rot_z(m, -90 * M_PI / 180);
	normalize(norm);
	transformvec(m, norm, tang);
	norm[2] = (obj->radius / obj->scale[0]);
	if (ABS(lpoint[2]) > ((obj->scale[0] / 2.0) * 0.99999))
	{
		FILLVEC(norm, 0, 0, lpoint[2] < 0 ? -1 : 1, 0);
		FILLVEC(tang, lpoint[2] < 0 ? -1 : 1, 0, 0, 0);
	}
	normalize(norm);
	norm_offset(norm, tang, c->hold);
	transformvec(obj->otw, norm, norm);
}

static int	get_abc(double t[3], t_ray *tr, t_obj *obj)
{
	double	var[3];
	double	c;

	if (!tr->dir[2])
		t[2] = -1;
	else
		t[2] = (-obj->scale[0] / 2.0 - tr->org[2]) / tr->dir[2];
	c = pow(obj->radius / obj->scale[0], 2);
	var[0] = tr->dir[0] * tr->dir[0] + tr->dir[1] * tr->dir[1]
				- c * tr->dir[2] * tr->dir[2];
	var[1] = 2 * (tr->org[0] * tr->dir[0] + tr->org[1] * tr->dir[1]
				- c * (tr->org[2] - obj->scale[0] / 2) * tr->dir[2]);
	var[2] = tr->org[0] * tr->org[0] + tr->org[1] * tr->org[1] -
				c * pow((tr->org[2] - obj->scale[0] / 2), 2);
	if (!quad(var, t))
		return (0);
	return (1);
}

static void	cone_bound(t_obj *obj, double t[3], t_ray *tr)
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
	if (t[0] < 0)
		t[0] = t[1];
	t[1] = t[2];
	if (t[1] < t[0])
		ft_swap(&t[0], &t[1], sizeof(double));
}

int			cone_intersect(t_ray *ray, t_obj *obj)
{
	t_ray	tr;
	double	t[3];

	transformvec(obj->wto, ray->dir, tr.dir);
	transform(obj->wto, ray->org, tr.org);
	tr.len = ray->len;
	if (!get_abc(t, &tr, obj))
	{
		t[0] = -1;
		t[1] = -1;
	}
	cone_bound(obj, t, &tr);
	if (t[0] < 0)
		t[0] = t[1];
	if (t[0] < 0 || t[0] > ray->len)
		return (0);
	ray->len = t[0];
	return (1);
}
