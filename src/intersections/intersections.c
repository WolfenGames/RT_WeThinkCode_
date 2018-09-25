/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 12:25:58 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/25 15:53:34 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	This function is used to scale the objects colour by the amount of light
**	hitting the object at that point.
**
**	The amount of light that hits the object is based on the light intensity,
**	distance from light source and angle of the light to the surface of the
**	object.
**
**	The vectors used in this function are put into an array for the purposes of
**	norming.
**	vec[0] is the amount of light hitting the object in the sense of RGB
**	vec[1] is a temperary vector
**	vec[2] is the normal of the object at that point
*/

static double	shade(double dot, double shaded, t_obj *obj)
{
	dot += obj->trans;
	dot = ft_min(1, dot);
	if (!shaded)
		return (dot);
	dot *= 1 / shaded;
	dot = (int)dot;
	dot *= shaded;
	dot += shaded;
	dot = ft_min(1, dot);
	return (dot);
}

static void		light_thing(t_ray point[4], t_env *env, t_obj *obj, t_ray *c)
{
	t_list	*cur;
	t_vec	vecs[3];
	t_col	col;

	cur = env->scene.lig;
	vecs[2][3] = point[0].tri_index;
	vecs[2][2] = point[0].v;
	vecs[2][1] = point[0].u;
	sc_col(c->dir, 0.01, vecs[0]);
	while (cur)
	{
		generate_shadow_ray(&point[0], LIG, env, col);
		sc_col(col, (obj->albedo / M_PI) * (LIG->intensity
			/ (LIG->type == light_point ? point[0].len : 1.0))
			* shade(ABS(dot(point[0].dir, point[2].dir)), env->scene.cellshade, obj),
			vecs[1]);
		add_col(vecs[0], vecs[1], vecs[0]);
		cur = cur->next;
	}
	add_col(vecs[0], env->ambience, vecs[0]);
	c->dir[0] *= vecs[0][0] / 255.0;
	c->dir[1] *= vecs[0][1] / 255.0;
	c->dir[2] *= vecs[0][2] / 255.0;
}

void			reflect_crap(t_ray *c, t_ray point[3], t_obj *obj, double k)
{
	t_col	specular_rat;
	t_col	refract;

	v_multi(c->org, 1 / 255.0, specular_rat);
	refract[0] = (point[3].dir[0] / 255.0) * point[1].org[0];
	refract[1] = (point[3].dir[1] / 255.0) * point[1].org[1];
	refract[2] = (point[3].dir[2] / 255.0) * point[1].org[2];
	k *= 1 - obj->trans;
	k += 1 - obj->trans;
	c->dir[0] = ft_clamp(255, 0, specular_rat[0] * point[1].dir[0] * k + (c->dir[0])
		* (1 - obj->trans) + point[1].org[0] * (obj->trans) * (1 - k));
	c->dir[1] = ft_clamp(255, 0, specular_rat[1] * point[1].dir[1] * k + (c->dir[1])
		* (1 - obj->trans) + point[1].org[1] * (obj->trans) * (1 - k));
	c->dir[2] = ft_clamp(255, 0, specular_rat[2] * point[1].dir[2] * k + (c->dir[2])
		* (1 - obj->trans) + point[1].org[2] * (obj->trans) * (1 - k));
}

static void		mid(t_ray *ray, t_ray point[4], t_env *env, t_obj *hit_obj)
{
	memcpy(&point[0], ray, sizeof(t_ray));
	v_add(v_multi(ray->dir, ray->len * 0.9999999, point[0].org),
		ray->org, point[0].org);
	hit_obj->get_surface_col(hit_obj, &point[3], point[0].org);
	hit_obj->get_norm(point[2].dir, point[0].org, hit_obj, &point[3]);
	vec_dup(point[3].dir, point[1].org);
	if ((REFLECTIVE || REFRACTIVE) && point[2].len < env->scene.raydepth)
	{
		refract(ray->dir, point[2].dir, hit_obj->r_index, point[0].dir);
		v_add(point[0].org,
			v_multi(point[2].dir, 0.00000003 *
				(dot(point[2].dir, point[0].dir) < 0 ? -1 : 1),
				point[2].org), point[0].org);
		if (hit_obj->trans)
			get_col(&point[0], env, point[1].org, point[2].len + 1);
		v_sub(point[0].org, point[2].org, point[0].org);
		vec_dup(point[1].org, point[1].dir);
		if (REFLECTIVE && reflect(ray->dir, point[2].dir, point[0].dir))
			get_col(&point[0], env, point[1].dir, point[2].len + 1);
		reflect_crap(&point[3], point, hit_obj,
			fresnel(ray->dir, point[2].dir, hit_obj->r_index));
	}
	light_thing(point, env, hit_obj, &point[3]);
	//FILLCOL(point[3].dir, (point[2].dir[0] + 1) * 127, (point[2].dir[1] + 1) * 127, (point[2].dir[2] + 1) * 127, 0);
	//vec_dup(point[3].hold, point[3].dir);
	//FILLCOL(point[3].dir, point[3].tri_index == 0 ? (point[3].u / (2 * M_PI)) * 255 : 0, point[3].tri_index == 1 ? (point[3].u / (2 * M_PI)) * 255 : 0, point[3].tri_index == 2 ? (point[3].u / (2 * M_PI)) * 255 : 0, 0);
}

/*
**	point[0] = temp ray
**	point[1].org = refract col
**	point[1].dir = reflect col
**	point[2].org = tempvec
**	point[2].dir = normal
**	point[3].org = specular col
**	point[3].dir = surface col
**	point[3].hold = norm col
*/

void			get_col(t_ray *ray, t_env *env, t_col c, int level)
{
	t_obj	*hit_obj;
	t_ray	point[4];

	ray->len = INFINITY;
	ray->u = 0;
	ray->tri_index = 0;
	ray->v = 0;
	hit_obj = trace(ray, env->scene.obj);
	point[2].len = level;
	point[2].dir[3] = ray->tri_index;
	point[2].dir[2] = ray->v;
	point[2].dir[1] = ray->u;
	point[3].dir[3] = ray->tri_index;
	point[3].dir[2] = ray->v;
	point[3].dir[1] = ray->u;
	if (hit_obj)
		mid(ray, point, env, hit_obj);
	else
		vec_dup(env->ambience, point[3].dir);
	vec_dup(point[3].dir, c);
	c[3] = 255;
	glare(ray, env, c);
}
