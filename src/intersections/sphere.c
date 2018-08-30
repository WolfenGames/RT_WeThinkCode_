/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 17:11:48 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/30 12:57:21 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	sphere_getnorm(t_vec norm, t_vec point, t_obj *obj)
{
	v_sub(point, obj->org, norm);
//	if (length(norm) < 1)
//		v_multi(norm, -1, norm);
	normalize(norm);
}

int		sphere_intersect(t_ray *ray, t_obj *obj)
{
	t_vec	l;
	t_vec	var;
	double	t[2];

	v_sub(ray->org, obj->org, l);
	var[0] = dot(ray->dir, ray->dir);
	var[1] = 2 * dot(ray->dir, l);
	var[2] = dot(l, l) - 1.0;
	if (!quad(var, t))
		return (0);
	if (t[0] < 0)
		t[0] = t[1];
	if (t[0] < 0)
		return (0);
	if (t[0] > ray->len)
		return (0);
	ray->len = t[0];
	return (1);
}