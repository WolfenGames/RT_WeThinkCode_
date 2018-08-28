/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 17:11:48 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/28 17:52:44 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

int		sphere_intersect(t_ray *ray, t_obj *obj)
{
	t_vec	l;
	double	a;
	double	b;
	double	c;
	double	t[2];

	v_sub(ray->org, obj->org, l);
	a = dot(ray->dir, ray->dir);
	b = 2 * dot(ray->dir, l);
	c = dot(l, l) - 1;
	if (!quad(a, b, c, t))
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