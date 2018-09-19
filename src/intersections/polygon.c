/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygon.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 13:20:45 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/19 10:25:18 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	poly_surface_col(t_obj *obj, t_col c, t_vec point)
{
	int i;
	t_vec	len;
	t_vec	o;

	(void)point;
	i = c[3];
	if (!obj->tex)
	{
		vec_dup(obj->surface_colour, c);
		return ;
	}
	len[1] = c[1];
	len[2] = c[2];
	len[0] = 1 - c[1] - c[2];
	o[0] = VT(2)[0] * len[0];
	o[1] = VT(2)[1] * len[0];
	o[0] += VT(0)[0] * len[1];
	o[1] += VT(0)[1] * len[1];
	o[0] += VT(1)[0] * len[2];
	o[1] += VT(1)[1] * len[2];
	o[1] = 1 - o[1];
	FILLCOL(c, o[0] * 255, o[1] * 255, 255, 0);
	o[0] *= obj->tex->w;
	o[1] *= obj->tex->h;
	get_img_col(o[0], o[1], obj->tex, c);
}

void	poly_getnorm(t_vec norm, t_vec point, t_obj *obj)
{
	int i;
	t_vec	len;
	t_vec	temp;

	(void)point;
	i = norm[3];
	len[1] = norm[1];
	len[2] = norm[2];
	len[0] = 1 - norm[1] - norm[2];
	v_add(v_multi(VN(2), len[0], temp), v_multi(VN(0), len[1], norm), norm);
	v_add(norm, v_multi(VN(1), len[2], temp), norm);
	transformvec(obj->otw, norm, norm);
}

int		tri_intersect(t_ray	*ray, t_ray *tr, t_obj *obj, int i)
{
	t_vec	v1v0;
	t_vec	v2v0;
	t_vec	norm;
	double	area2;

	v_sub(VP(1), VP(0), v1v0);
	v_sub(VP(2), VP(0), v2v0);
	v_cross(v1v0, v2v0, norm);
	area2 = length(norm);

	double	NdotDir = dot(norm, tr->dir);
	if (ABS(NdotDir) < EPSILON)
		return (0);
	double d = dot(norm, VP(0));
	double t = (-dot(norm, tr->org) + d) / NdotDir;
	if (t < 0 || t > ray->len)
		return(0);
	t_vec	point;
	v_add(tr->org, v_multi(tr->dir, t, point), point);
	t_vec	perp;
	t_vec	topoint;
	v_sub(point, VP(0), topoint);
	v_cross(v1v0, topoint, perp);
	if (dot(norm, perp) < 0)
		return (0);
	t_vec	v2v1;
	v_sub(VP(2), VP(1), v2v1);
	v_sub(point, VP(1), topoint);
	v_cross(v2v1, topoint, perp);
	d = length(perp) / area2;
	if (dot(norm, perp) < 0)
		return (0);
	t_vec	v0v2;
	v_sub(VP(0), VP(2), v0v2);
	v_sub(point, VP(2), topoint);
	v_cross(v0v2, topoint, perp);
	area2 = length(perp) / area2;
	if (dot(norm, perp) < 0)
		return (0);
	ray->len = t;
	ray->u = d;
	ray->v = area2;
	ray->tri_index = i;
	return (1);
}

int		poly_intersect(t_ray *ray, t_obj *obj)
{
	t_ray   tr;
	int i;
	int hitthis;

	i = -1;
	hitthis = 0;
	transformvec(obj->wto, ray->dir, tr.dir);
	transform(obj->wto, ray->org, tr.org);
	while (++i < obj->n_faces)
		if (tri_intersect(ray, &tr, obj, i))
			hitthis = 1;
	if (hitthis)
		return (1);
	return (0);
}
