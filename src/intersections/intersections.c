/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 12:25:58 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/10 07:49:41 by jwolf            ###   ########.fr       */
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

void			reflect_crap(t_col c, t_col ref[2], t_obj *obj)
{
	t_col	specular_rat;
	t_col	refract;

	specular_rat[0] = obj->specular_colour[0] / 255.0;
	specular_rat[1] = obj->specular_colour[1] / 255.0;
	specular_rat[2] = obj->specular_colour[2] / 255.0;
	refract[0] = (obj->surface_colour[0] / 255.0) * ref[1][0];
	refract[1] = (obj->surface_colour[1] / 255.0) * ref[1][1];
	refract[2] = (obj->surface_colour[2] / 255.0) * ref[1][2];
	c[0] = specular_rat[0] * ref[0][0] + c[0];// * obj->transparency + ref[1][0] * (1 - obj->transparency);
	c[1] = specular_rat[1] * ref[0][1] + c[1];// * obj->transparency + ref[1][1] * (1 - obj->transparency);
	c[2] = specular_rat[2] * ref[0][2] + c[2];// * obj->transparency + ref[1][2] * (1 - obj->transparency);
	//FILLCOL(c, refract[0], refract[1], refract[2], refract[3]);
}

void			get_col(t_ray *ray, t_env *env, t_col c, int level)
{
	t_obj	*hit_obj;
	t_ray	point;
	t_col	reflect_col[2];
	t_vec	norm;

	ray->len = INFINITY;
	hit_obj = trace(ray, env);
	if (hit_obj)
	{
		v_add(v_multi(ray->dir, ray->len * 0.999999999, point.org),
			ray->org, point.org);
		hit_obj->get_surface_col(hit_obj, c, point.org);
		hit_obj->get_norm(norm, point.org, hit_obj);
		if ((REFLECTIVE || REFRACTIVE) && level < 5)
		{
			reflect(ray->dir, norm, point.dir);
			if (REFLECTIVE)
				get_col(&point, env, reflect_col[0], level + 1);
			//v_add(point.org, v_multi(ray->dir, 0.0000001, point.dir), point.org);
			//refract(ray->dir, norm, hit_obj->r_index, point.dir);
			//if (hit_obj->transparency)
				//get_col(&point, env, reflect_col[1], level + 1);
			//v_sub(point.org, v_multi(ray->dir, 0.0000001, point.dir), point.org);
			reflect_crap(c, reflect_col, hit_obj);
		}
		light_thing(&point, env, hit_obj, c);
	}
	else
		FILLCOL(c, 5, 5, 5, 255);
	c[3] = 255;
	glare(ray, env, c);
}
