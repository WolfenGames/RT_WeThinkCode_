/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 12:25:58 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/11 18:10:51 by ibotha           ###   ########.fr       */
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

double	fresnel(t_vec inc, t_vec norm, double index)
{
	double	ret;
	double	cosi = ft_clamp(1, -1, dot(inc, norm));
    double	etai = 1;
	double	etat = index;

    if (cosi > 0)
		ft_swap(&etai, &etat, sizeof(double));
    double sint = etai / etat * sqrt(ft_max(0.0, 1 - cosi * cosi));
    if (sint >= 1) { 
        ret = 1; 
    } 
    else
	{ 
        double	cost = sqrt(ft_max(0.0, 1 - sint * sint));
        cosi = ABS(cosi);
        double	Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
        double	Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
        ret = (Rs * Rs + Rp * Rp) / 2.0;
    }
	return (ret);
}

void			reflect_crap(t_col c, t_col ref[2], t_obj *obj, double k)
{
	t_col	specular_rat;
	t_col	refract;

	specular_rat[0] = obj->specular_colour[0] / 255.0;
	specular_rat[1] = obj->specular_colour[1] / 255.0;
	specular_rat[2] = obj->specular_colour[2] / 255.0;
	refract[0] = (obj->surface_colour[0] / 255.0) * ref[1][0];
	refract[1] = (obj->surface_colour[1] / 255.0) * ref[1][1];
	refract[2] = (obj->surface_colour[2] / 255.0) * ref[1][2];
	c[0] = specular_rat[0] * ref[0][0] * k + (c[0]) * (1 - obj->transparency)
		+ ref[1][0] * (obj->transparency) * (1 - k);
	c[1] = specular_rat[1] * ref[0][1] * k + (c[1]) * (1 - obj->transparency)
		+ ref[1][1] * (obj->transparency) * (1 - k);
	c[2] = specular_rat[2] * ref[0][2] * k + (c[2]) * (1 - obj->transparency)
		+ ref[1][2] * (obj->transparency) * (1 - k);
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
		if ((REFLECTIVE || REFRACTIVE) && level < env->scene.raydepth)
		{
			if (REFLECTIVE)
				if (reflect(ray->dir, norm, point.dir))
					get_col(&point, env, reflect_col[0], level + 1);
			v_add(point.org, v_multi(ray->dir, 0.0001, point.dir), point.org);
			refract(ray->dir, norm, hit_obj->r_index, point.dir);
			if (hit_obj->transparency)
				get_col(&point, env, reflect_col[1], level + 1);
			v_sub(point.org, v_multi(ray->dir, 0.0001, point.dir), point.org);
			reflect_crap(c, reflect_col, hit_obj, fresnel(ray->dir, norm, hit_obj->r_index));
		}
		light_thing(&point, env, hit_obj, c);
	}
	else
		FILLCOL(c, 0, 0, 0, 255);
	c[3] = 255;
	glare(ray, env, c);
}
