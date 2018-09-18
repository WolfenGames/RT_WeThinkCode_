/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 12:25:58 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/18 18:34:57 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	The trace function takes a ray and determines if it hits an object,
**	it shortens the ray to the distance to the point of intersection and
**	returns the hit object.
*/

t_obj		*trace(t_ray *ray, t_list *cur)
{
	t_obj	*ret;

	ret = NULL;
	while (cur)
	{
		if (((t_obj*)cur->content)->get_intersect(ray, cur->content))
			ret = (t_obj*)cur->content;
		cur = cur->next;
	}
	return (ret);
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
	t_col	col;

	cur = env->scene.lig;
	vecs[2][3] = shadow->tri_index;
	vecs[2][2] = shadow->v;
	vecs[2][1] = shadow->u;
	obj->get_norm(vecs[2], shadow->org, obj);
	sc_col(c, 0.01, vecs[0]);
	while (cur)
	{
		generate_shadow_ray(shadow, LIG, env, col);
		sc_col(col, (obj->albedo / M_PI) * (LIG->intensity
			/ (LIG->type == light_point ? DIV_P(shadow->len) : 1.0))
			* ABS(dot(shadow->dir, vecs[2])), vecs[1]);
		add_col(vecs[0], vecs[1], vecs[0]);
		cur = cur->next;
	}
	c[0] *= vecs[0][0] / 255.0;
	c[1] *= vecs[0][1] / 255.0;
	c[2] *= vecs[0][2] / 255.0;
}

void			reflect_crap(t_col c, t_ray point[3], t_obj *obj, double k)
{
	t_col	specular_rat;
	t_col	refract;

	specular_rat[0] = obj->specular_colour[0] / 255.0;
	specular_rat[1] = obj->specular_colour[1] / 255.0;
	specular_rat[2] = obj->specular_colour[2] / 255.0;
	refract[0] = (point[3].dir[0] / 255.0) * point[1].org[0];
	refract[1] = (point[3].dir[1] / 255.0) * point[1].org[1];
	refract[2] = (point[3].dir[2] / 255.0) * point[1].org[2];
	c[0] = ft_clamp(255, 0, specular_rat[0] * point[1].dir[0] * k + (c[0])
		* (1 - obj->transparency) + point[1].org[0] * (obj->transparency) * (1 - k));
	c[1] = ft_clamp(255, 0, specular_rat[1] * point[1].dir[1] * k + (c[1])
		* (1 - obj->transparency) + point[1].org[1] * (obj->transparency) * (1 - k));
	c[2] = ft_clamp(255, 0, specular_rat[2] * point[1].dir[2] * k + (c[2])
		* (1 - obj->transparency) + point[1].org[2] * (obj->transparency) * (1 - k));
}

static void		mid(t_ray *ray, t_ray point[3], t_env *env, t_obj *hit_obj)
{
	memcpy(&point[0], ray, sizeof(t_ray));
	v_add(v_multi(ray->dir, ray->len * 0.999999999, point[0].org),
		ray->org, point[0].org);
	point[3].dir[3] = ray->tri_index;
	hit_obj->get_surface_col(hit_obj, point[3].dir, point[0].org);
	point[2].dir[3] = ray->tri_index;
	point[2].dir[2] = ray->v;
	point[2].dir[1] = ray->u;
	hit_obj->get_norm(point[2].dir, point[0].org, hit_obj);
	if ((REFLECTIVE || REFRACTIVE) && point[2].len < env->scene.raydepth)
	{
		if (REFLECTIVE && reflect(ray->dir, point[2].dir, point[0].dir))
				get_col(&point[0], env, point[1].dir, point[2].len + 1);
		refract(ray->dir, point[2].dir, hit_obj->r_index, point[0].dir);
		v_add(point[0].org, v_multi(point[0].dir, 0.000001, point[2].org), point[0].org);
		if (hit_obj->transparency)
			get_col(&point[0], env, point[1].org, point[2].len + 1);
		v_sub(point[0].org, point[2].org, point[0].org);
		reflect_crap(point[3].dir, point, hit_obj,
			fresnel(ray->dir, point[2].dir, hit_obj->r_index * hit_obj->transparency));
	}
	light_thing(&point[0], env, hit_obj, point[3].dir);
}

void			get_col(t_ray *ray, t_env *env, t_col c, int level)
{
	t_obj	*hit_obj;
	t_ray	point[4];

	ray->len = INFINITY;
	hit_obj = trace(ray, env->scene.obj);
	point[2].len = level;
	FILLCOL(point[3].dir, 0, 0, 0, 255);
	if (hit_obj)
		mid(ray, point, env, hit_obj);
	vec_dup(point[3].dir, c);
	c[3] = 255;
	glare(ray, env, c);
}
