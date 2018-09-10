/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 14:50:41 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/10 15:36:42 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	plane_surface_col(t_obj *ob, t_col c, t_vec point)
{
	/* t_vec		norm;
	t_vec		tempvec[3];
	t_vec		o;
	t_img		*img = ob->tex;

	transform(ob->wto, point, tempvec[2]);
	plane_getnorm(norm, tempvec[2], ob);
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
	o[0] = 1 - ((norm[0] < 0 ? 0 : 2 * M_PI)) / (2.f * M_PI)
		* find_angle(tempvec[0], tempvec[1]) / (2.f * M_PI);
	o[0] = (o[0] * ob->tex_scale[0] - (int)(o[0] * ob->tex_scale[0])) * img->w;
	o[1] = (o[1] * ob->tex_scale[1] - (int)(o[1] * ob->tex_scale[1])) * img->h;
	get_img_col(o[0], o[1], img, c); */
	(void)ob;
	(void)point;
	FILLCOL(c, ob->surface_colour[0], ob->surface_colour[1],
		ob->surface_colour[2], ob->surface_colour[3]);
}

void	plane_getnorm(t_vec norm, t_vec point, t_obj *obj)
{
	t_vec	lpoint;

	FILLVEC(norm, 0, 0, 1, 0);
	transform(obj->wto, point, lpoint);
	if (lpoint[2] < 0)
		v_multi(norm, -1, norm);
	transformvec(obj->otw, norm, norm);
}

int		plane_intersect(t_ray *ray, t_obj *obj)
{
	t_ray	tr;
	double	t;

	transformvec(obj->wto, ray->dir, tr.dir);
	transform(obj->wto, ray->org, tr.org);
	if (!((tr.org[2] < 0 && tr.dir[2] > 0) || (tr.org[2] > 0 && tr.dir[2] < 0)))
		return (0);
	normalize(tr.dir);
	t = ABS(tr.org[2] / tr.dir[2]) - 0.0001;
	if (ray->len < t)
		return (0);
	ray->len = t;
	return (1);
}