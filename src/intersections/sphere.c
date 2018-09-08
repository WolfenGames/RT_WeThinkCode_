/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 17:11:48 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/08 12:58:28 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	sphere_surface_col(t_obj *ob, t_col c, t_vec point)
{
	t_vec		norm;
	t_vec		tempvec[3];
	t_vec		o;
	t_img		*img = ob->tex;

	transform(ob->wto, point, tempvec[2]);
	sphere_getnorm(norm, tempvec[2], ob);
	if (!img)
	{
		FILLCOL(c, ob->surface_colour[0], ob->surface_colour[1],
			ob->surface_colour[2], ob->surface_colour[3]);
		return ;
	}
	FILLVEC(tempvec[0], 0, 1, 0, 0);
	o[1] = (find_angle(norm, tempvec[0]) / M_PI);
	FILLVEC(tempvec[1], norm[0], 0, norm[2], 0);
	FILLVEC(tempvec[0], 0, 0, 1, 0);
	o[0] = 1 - ((norm[0] < 0 ? 0 : 2 * M_PI) + (norm[0] < 0 ? 1 : -1)
		* find_angle(tempvec[0], tempvec[1])) / (2.f * M_PI);
	o[0] = (o[0] * ob->tex_scale[0] - (int)(o[0] * ob->tex_scale[0])) * img->w;
	o[1] = (o[1] * ob->tex_scale[1] - (int)(o[1] * ob->tex_scale[1])) * img->h;
	get_img_col(o[0], o[1], img, c);
}

void	sphere_getnorm(t_vec norm, t_vec point, t_obj *obj)
{
	v_sub(point, obj->org, norm);
	if (length(norm) < obj->radius)
		v_multi(norm, -1, norm);
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
	var[2] = dot(l, l) - (obj->radius * obj->radius);
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