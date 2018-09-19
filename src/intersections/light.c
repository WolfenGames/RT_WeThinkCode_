/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 14:20:25 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/19 11:44:39 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		cap_col(double o[2], t_vec lpoint, t_obj *obj)
{
	o[0] = (ABS(lpoint[0] + obj->radius) / (obj->radius * 2));
	o[1] = (ABS(lpoint[1] + obj->radius) / (obj->radius * 2));
}

static int	visible(t_ray *ray, t_lig *lig, t_env *env)
{
	t_ray	vis;

	vec_dup(ray->org, vis.org);
	v_sub(lig->org, vis.org, vis.dir);
	vis.len = length(vis.dir);
	normalize(vis.dir);
	if (dot(vis.dir, ray->dir) < 0)
		return (0);
	if (trace(&vis, env->scene.obj))
		return (0);
	return (1);
}

static void	check_light(t_ray *ray, t_lig *lig, t_col c, t_env *env)
{
	t_vec	l;
	t_col	b;
	double	dot_l_r;
	double	light_length;

	v_sub(lig->org, ray->org, l);
	light_length = length(l);
	if (!visible(ray, lig, env))
		return ;
	normalize(l);
	dot_l_r = dot(l, ray->dir);
	if (dot_l_r < 0)
		return ;
	sc_col(lig->col, pow(dot_l_r, (10000 * light_length) / lig->intensity), b);
	add_col(c, b, c);
}

void		glare(t_ray *ray, t_env *env, t_col c)
{
	t_list *cur;

	cur = env->scene.lig;
	while (cur)
	{
		if (LIG->type == light_point)
			check_light(ray, cur->content, c, env);
		cur = cur->next;
	}
}
