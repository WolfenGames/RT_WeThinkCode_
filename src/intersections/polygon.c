/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygon.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 13:20:45 by jwolf             #+#    #+#             */
/*   Updated: 2019/06/17 12:59:26 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Each C = Case;
** Each case looks to see if the information is valid, or invalid;
*/

#define T1 (obj->faces[i][0][1] >= obj->n_v_t_coord || obj->faces[i][0][1] < 0)
#define T2 (obj->faces[i][1][1] >= obj->n_v_t_coord || obj->faces[i][1][1] < 0)
#define T3 (obj->faces[i][2][1] >= obj->n_v_t_coord || obj->faces[i][2][1] < 0)
#define P1 (obj->faces[i][0][0] >= obj->n_v_point || obj->faces[i][0][0] < 0)
#define P2 (obj->faces[i][1][0] >= obj->n_v_point || obj->faces[i][1][0] < 0)
#define P3 (obj->faces[i][2][0] >= obj->n_v_point || obj->faces[i][2][0] < 0)
#define N1 (obj->faces[i][0][2] >= obj->n_v_normal || obj->faces[i][0][2] < 0)
#define N2 (obj->faces[i][1][2] >= obj->n_v_normal || obj->faces[i][1][2] < 0)
#define N3 (obj->faces[i][2][2] >= obj->n_v_normal || obj->faces[i][2][2] < 0)
#define LEN temp[3]
#define O1 (VT(2)[1] * LEN[0] + VT(0)[1] * LEN[1] + VT(1)[1] * LEN[2])
#define O0 (VT(2)[0] * LEN[0] + VT(0)[0] * LEN[1] + VT(1)[0] * LEN[2])

void	poly_surface_col(t_obj *obj, t_ray *c, t_vec point)
{
	int		i;
	t_vec	temp[4];

	i = c->dir[3];
	temp[3][1] = c->dir[1];
	temp[3][2] = c->dir[2];
	temp[3][0] = 1 - c->dir[1] - c->dir[2];
	vec_dup(obj->specular_colour, c->org);
	vec_dup(obj->surface_colour, c->dir);
	FILLVEC(c->hold, 128, 128, 255, 0);
	if (T1 || T2 || T3)
		return ;
	FILLVEC(temp[2], O0, O1, 0, 0);
	if (VT(0)[0] > VT(1)[0])
		c->tri_index = VT(0)[0] > VT(2)[0] ? 0 : 2;
	else
		c->tri_index = VT(1)[0] > VT(2)[0] ? 1 : 2;
	poly_surface_col_cont(temp, obj, c, point);
	FILLVEC(temp[0], 1, 0, 0, 0);
	FILLVEC(temp[1], VT(c->tri_index)[0] - temp[2][0],
		VT(c->tri_index)[1] - temp[2][1], 0, 0);
	c->u = temp[2][1] < VT(c->tri_index)[1] ? find_angle(temp[0], temp[1]) :
		(2 * M_PI - find_angle(temp[0], temp[1]));
}

void	poly_getnorm(t_vec norm, t_vec point, t_obj *obj, t_ray *c)
{
	int			i;
	t_vec		len;
	t_vec		temp;
	t_matrix	m;

	i = norm[3];
	len[1] = norm[1];
	len[2] = norm[2];
	len[0] = 1 - norm[1] - norm[2];
	if (N1 || N2 || N3)
		return ;
	v_add(v_multi(VN(2), len[0], temp), v_multi(VN(0), len[1], norm), norm);
	v_add(norm, v_multi(VN(1), len[2], temp), norm);
	normalize(norm);
	if (obj->norm && (obj->faces[i][c->tri_index][0] < obj->n_v_point
		&& obj->faces[i][c->tri_index][0] >= 0))
	{
		fill_m_rot_v(-c->u, norm, m);
		transform(obj->wto, point, temp);
		v_sub(VP(c->tri_index), temp, temp);
		transformvec(m, temp, temp);
		normalize(temp);
		norm_offset(norm, temp, c->hold);
	}
	transformvec(obj->otw, norm, norm);
}

int		left_of(t_vec to, t_vec from, t_vec point[2], t_vec perp)
{
	t_vec	to_from;
	t_vec	to_point;

	v_sub(to, from, to_from);
	v_sub(point[1], from, to_point);
	v_cross(to_from, to_point, perp);
	if (dot(point[0], perp) < 0)
		return (0);
	return (1);
}

int		tri_intersect(t_ray *ray, t_ray *tr, t_obj *obj, int i)
{
	t_vec	norm[6];
	double	var[3];

	if ((obj->faces[i][0][0] >= obj->n_v_point || obj->faces[i][0][0] < 0) ||
		(obj->faces[i][1][0] >= obj->n_v_point || obj->faces[i][1][0] < 0) ||
		(obj->faces[i][2][0] >= obj->n_v_point || obj->faces[i][2][0] < 0))
		return (0);
	v_sub(VP(1), VP(0), norm[2]);
	v_sub(VP(2), VP(0), norm[3]);
	v_cross(norm[2], norm[3], norm[0]);
	var[0] = length(norm[0]);
	var[1] = dot(norm[0], tr->dir);
	if (ABS(var[1]) < EPSILON)
		return (0);
	var[2] = (-dot(norm[0], tr->org) + dot(norm[0], VP(0))) / var[1];
	v_add(tr->org, v_multi(tr->dir, var[2], norm[1]), norm[1]);
	if (var[2] < 0 || var[2] > ray->len || !left_of(VP(1), VP(0), norm, norm[4])
		|| !left_of(VP(2), VP(1), norm, norm[4])
		|| !left_of(VP(0), VP(2), norm, norm[5]))
		return (0);
	ray->u = length(norm[4]) / var[0];
	ray->v = length(norm[5]) / var[0];
	ray->len = var[2];
	ray->tri_index = i;
	return (1);
}

int		poly_intersect(t_ray *ray, t_obj *obj)
{
	t_ray	tr;
	int		i;
	int		hitthis;

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
