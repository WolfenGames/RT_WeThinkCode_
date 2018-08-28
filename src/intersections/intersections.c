/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 12:25:58 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/28 18:59:10 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

static t_obj	*trace(t_ray *ray, t_env *env)
{
	t_obj	*ret;
	t_list	*cur;

	ret = NULL;
	cur = env->scene.obj;
	while (cur)
	{
		if (((t_obj*)cur->content)->type == obj_sphere)
			if (sphere_intersect(ray, cur->content))
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
		normalize(shadow->dir);
	}
	if (trace(shadow, env))
		return (0);
	return (1);
}

static void	get_norm(t_vec norm, t_vec point, t_obj *obj)
{
	if (obj->type == obj_sphere)
		sphere_getnorm(norm, point, obj);
}

static void	light_thing(t_ray *shadow, t_env *env, t_obj *obj, t_col c)
{
	t_list	*cur;
	t_col	light_col;
	t_col	temp;
	t_vec	norm;

	cur = env->scene.lig;
	get_norm(norm, shadow->org, obj);
	ft_bzero(light_col, sizeof(double) * 4);
	while (cur)
	{
		if (generate_shadow_ray(shadow, LIG, env))
		{
			add_col(light_col, sc_col(LIG->col,
				(obj->albedo / M_PI)
				* (LIG->intensity / (LIG->type == light_point ? shadow->len : 1))
				* dot(shadow->dir, norm),
				temp), light_col);
		}
		cur = cur->next;
	}
	c[0] *= light_col[0] / 255.0;
	c[1] *= light_col[1] / 255.0;
	c[2] *= light_col[2] / 255.0;
}

void			get_col(t_ray *ray, t_env *env, t_col c)
{
	t_obj	*hit_obj;
	t_ray	point;

	ray->len = INFINITY;
	hit_obj = trace(ray, env);
	if (hit_obj)
	{
		v_add(v_multi(ray->dir, ray->len - 0.000001, point.org), ray->org, point.org);
		ft_memcpy(c, hit_obj->surface_colour, sizeof(double) * 4);
		light_thing(&point, env, hit_obj, c);
	}
	else
		FILLCOL(c, 0, 0, 0, 255);
	c[3] = 255;
}
