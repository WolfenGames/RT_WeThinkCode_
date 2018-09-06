/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 12:25:58 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/06 17:14:50 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

/*
**	The trace function takes a ray and determines if it hits an object,
**	it shortens the ray to the distance to the point of intersection and
**	returns the hit object.
*/

t_obj		*trace(t_ray *ray, t_env *env)
{
	t_obj	*ret;
	t_list	*cur;

	ret = NULL;
	cur = env->scene.obj;
	while (cur)
	{
		if (((t_obj*)cur->content)->get_intersect(ray, cur->content))
			ret = (t_obj*)cur->content;
		cur = cur->next;
	}
	return (ret);
}

static int		generate_shadow_ray(t_ray *shadow, t_lig *lig, t_env *env)
{
	if (lig->type == light_directional)
	{
		v_multi(lig->dir, -1, shadow->dir);
		shadow->len = INFINITY;
	}
	if (lig->type == light_point)
	{
		v_sub(lig->org, shadow->org, shadow->dir);
		shadow->len = length(shadow->dir);
	}
	normalize(shadow->dir);
	if (trace(shadow, env))
		return (0);
	return (1);
}

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

static void	light_thing(t_ray *shadow, t_env *env, t_obj *obj, t_col c)
{
	t_list	*cur;
	t_vec	vecs[3];

	cur = env->scene.lig;
	obj->get_norm(vecs[2], shadow->org, obj);
	FILLVEC(vecs[0], 5, 5, 5, 0);
	while (cur)
	{
		if (generate_shadow_ray(shadow, LIG, env))
		{
			sc_col(LIG->col, (obj->albedo / M_PI) * (LIG->intensity
				/ (LIG->type == light_point ? shadow->len : 1.0))
				* dot(shadow->dir, vecs[2]), vecs[1]);
			add_col(vecs[0], vecs[1], vecs[0]);
		}
		cur = cur->next;
	}
	c[0] *= vecs[0][0] / 255.0;
	c[1] *= vecs[0][1] / 255.0;
	c[2] *= vecs[0][2] / 255.0;
}

void			reflect_crap(t_col c, t_col ref, t_obj *obj)
{
	t_col	rat;

	rat[0] = obj->specular_colour[0] / 255.0;
	rat[1] = obj->specular_colour[1] / 255.0;
	rat[2] = obj->specular_colour[2] / 255.0;
	c[0] = rat[0] * ref[0] + c[0];
	c[1] = rat[1] * ref[1] + c[1];
	c[2] = rat[2] * ref[2] + c[2];
}

void			get_col(t_ray *ray, t_env *env, t_col c, int level)
{
	t_obj	*hit_obj;
	t_ray	point;
	t_col	reflect_col;
	t_vec	norm;

	ray->len = INFINITY;
	hit_obj = trace(ray, env);
	if (hit_obj)
	{
		v_add(v_multi(ray->dir, ray->len * 0.999999999, point.org),
			ray->org, point.org);
		hit_obj->get_surface_col(hit_obj, c, point.org);
		hit_obj->get_norm(norm, point.org, hit_obj);
		reflect(ray->dir, norm, point.dir);
		if ((VEC3_IS(hit_obj->specular_colour) || hit_obj->r_index) && level < 5)
		{
			get_col(&point, env, reflect_col, level + 1);
			reflect_crap(c, reflect_col, hit_obj);
		}
		light_thing(&point, env, hit_obj, c);
	}
	else
		FILLCOL(c, 5, 5, 5, 255);
	c[3] = 255;
	glare(ray, env, c);
}
