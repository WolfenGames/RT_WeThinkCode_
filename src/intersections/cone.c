/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 10:07:15 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/10 09:12:54 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	cone_surface_col(t_obj *ob, t_col c, t_vec point)
{
	t_vec		norm;
	t_vec		tempvec[4];
	t_vec		o;
	t_img		*img = ob->tex;

	transform(ob->wto, point, tempvec[2]);
	FILLVEC(tempvec[3], tempvec[2][0], tempvec[2][1], 0, 0);
	cone_getnorm(point, norm, ob);
	o[2] = find_angle(norm, tempvec[3]);
	if (!img)
	{
		FILLCOL(c, ob->surface_colour[0], ob->surface_colour[1],
			ob->surface_colour[2], ob->surface_colour[3]);
		return ;
	}
	o[0] = 1 - ((tempvec[2][0] < 0) ? (2 * M_PI - o[2]) : o[2]) / (2 * M_PI);
	o[1] = ((ob->scale[0] / 2) - tempvec[2][2]) / ob->scale[0];
	o[0] = (o[0] * ob->tex_scale[0] - (int)(o[0] * ob->tex_scale[0])) * img->w;
	o[1] = (o[1] * ob->tex_scale[1] - (int)(o[1] * ob->tex_scale[1])) * img->h;
	get_img_col(o[0], o[1], (t_img*)img, c);
}

void		cone_getnorm(t_vec norm, t_vec point, t_obj *obj)
{
	t_matrix    norm_rot;
    t_vec       tempvec;
    t_matrix    temp;
    double        a;

    FILLVEC(norm, 0, 1, 0, 0);
    FILLVEC(tempvec, point[0], point[1], 0, 0);
    a = atan((obj->radius) / obj->scale[0]);
    fill_m_rot_x(norm_rot, a);
    fill_m_rot_z(temp, find_angle(norm, tempvec) * (tempvec[0] < 0 ? -1 : 1));
    a = find_angle(norm, tempvec);
    m4_mult(norm_rot, temp, norm_rot);
    transformvec(norm_rot, norm, norm);
    if (length(tempvec) < (obj->radius *
        (1 - (point[2] / obj->scale[0] + 0.5))))
        v_multi(norm, -1, norm);
}

static int	get_abc(double near, double t[3], t_ray *ray, t_obj *obj)
{
	double	var[3];
	double	c;

	c = pow(obj->scale[0] / obj->radius, 2);
	var[0] = ray->dir[0] * ray->dir[0] + ray->dir[1] * ray->dir[1]
		- c * ray->dir[2] * ray->dir[2];
	var[1] = 2 * (ray->org[0] * ray->dir[0] + ray->org[1]
		* ray->dir[1]
		- c * (ray->org[2] - obj->scale[0] / 2) * ray->dir[2]);
	var[2] = ray->org[0] * ray->org[0] + ray->org[1] * ray->org[1]
		- c * (ray->org[2] - obj->scale[0] / 2)
		* (ray->org[2] - obj->scale[0] / 2);
	if (!quad(var, t))
		return (0);
	t[2] = t[0] < 0 ? t[1] : t[0];
	if (t[2] < 0 || t[2] > near)
		return (0);
	return (1);
}

static int	cone_bound(t_vec temp, t_obj *obj, double t[3], t_ray tempray)
{
	double c;

	if (temp[2] < -obj->scale[0] / 2
		|| temp[2] > obj->scale[0] / 2)
	{
		if (t[2] == t[1])
			return (0);
		t[2] = t[1];
		v_multi(tempray.dir, t[2], temp);
		v_add(tempray.org, temp, temp);
		c = atan2f(temp[1], temp[0]);
		if (c < 0.0f)
			c += 2.0f * M_PI;
		if (temp[2] < -obj->scale[0] / 2
			|| temp[2] > obj->scale[0] / 2)
			return (0);
	}
	return (1);
}

int			cone_intersect(t_ray *ray, t_obj *obj)
{
	t_vec	temp;
	t_ray	tempray;
	double	c;
	double	t[3];

	transformvec(obj->wto, ray->dir, tempray.dir);
	transform(obj->wto, ray->org, tempray.org);
	if (!get_abc(ray->len, t, &tempray, obj))
		return (0);
	v_multi(tempray.dir, t[2], temp);
	v_add(tempray.org, temp, temp);
	c = atan2f(temp[1], temp[0]);
	if (c < 0.0f)
		c += 2.0f * M_PI;
	if (!cone_bound(temp, obj, t, tempray))
		return (0);
	if (ray->len < t[2])
		return (0);
	ray->len = t[2];
	printf("Intersecting???\n");
	return (1);
}