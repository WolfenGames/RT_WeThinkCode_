/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 14:20:25 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/05 11:41:11 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

int	visible(t_ray *ray, t_lig *lig, t_env *env)
{
	t_ray	vis;

	vec_dup(ray->org, vis.org);
	v_sub(lig->org, vis.org, vis.dir);
	vis.len = length(vis.dir);
	normalize(vis.dir);
	if (trace(&vis, env))
		return (0);
	return (1);
}

static void	check_light(t_ray *ray, t_lig *lig, t_col c, t_env *env)
{
	t_vec	l;
	t_vec	var;
	double	t[2];
	t_col	b;

(void)env;
	v_sub(ray->org, lig->org, l);
	var[0] = dot(ray->dir, ray->dir);
	var[1] = 2 * dot(ray->dir, l);
	var[2] = dot(l, l) - ((lig->intensity * 0.16) * (lig->intensity * 0.16));
	if (!quad(var, t))
		return ;
	if (t[0] < 0 && t[1] < 0)
		return ;
	if (t[0] > ray->len)
		return ;
	if (!visible(ray, lig, env))
		return ;
	FILLCOL(b, 255, 255, 255, 255);
	sc_col(b, (pow(((t[1] < ray->len ? t[1] : ray->len )
		- t[0]) / (lig->intensity * 0.31999), 1000))
		/ 255.0, b);
	FILLCOL(b, b[0] * lig->col[0], b[1] * lig->col[1], b[2] * lig->col[2], 0);
	add_col(c, b, c);
}

void		glare(t_ray *ray, t_env *env, t_col c)
{
	t_list *cur;

	cur = env->scene.lig;
	while (cur)
	{
		check_light(ray, cur->content, c, env);
		cur = cur->next;
	}
}
