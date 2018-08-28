/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 12:25:58 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/28 18:09:53 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

int				quad(double a, double b, double c, double t[2])
{
	double discr;
	double q;

	discr = b * b - 4.f * a * c;
	if (discr < 0)
		return (0);
	else if (discr == 0)
	{
		t[1] = -0.5 * b / a;
		t[0] = t[1];
	}
	else
	{
		q = (b > 0) ? -0.5 * (b + sqrt(discr)) : -0.5 * (b - sqrt(discr));
		t[0] = q / a;
		t[1] = c / q;
	}
	if (t[0] > t[1])
		ft_swap(&t[0], &t[1], sizeof(double));
	return (1);
}

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

static double	inshadow(t_ray *shadow, t_env *env)
{
	t_list	*cur;
	double	intensity;

	cur = env->scene.lig;
	intensity = 0;
	while (cur)
	{
		if (LIG->type == light_directional)
		{
			v_multi(LIG->dir, -1, shadow->dir);
			shadow->len = INFINITY;
		}
		if (LIG->type == light_point)
		{
			v_sub(LIG->org, shadow->org, shadow->dir);
			shadow->len = length(shadow->dir);
		}
		if (trace(shadow, env))
			return (0);
		intensity += LIG->type == light_point ? LIG->intensity
			/ (shadow->len * shadow->len) : LIG->intensity;
		cur = cur->next;
	}
	return (intensity);
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
		sc_col(c, inshadow(&point, env), c);
	}
	else
		FILLCOL(c, 0, 0, 0, 255);
	c[3] = 255;
}
