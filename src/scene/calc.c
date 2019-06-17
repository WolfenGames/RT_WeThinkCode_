/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 11:15:02 by ibotha            #+#    #+#             */
/*   Updated: 2019/06/17 13:09:34 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	calc_obj(t_obj *obj)
{
	t_vec		tempvec;
	t_matrix	temp;

	fill_m_rot_x(obj->otw, (-obj->rot[0] * M_PI) / 180.f);
	fill_m_rot_y(temp, (obj->rot[1] * M_PI) / 180.f);
	m4_mult(obj->otw, temp, obj->otw);
	FILLVEC(tempvec, 0, 0, -1, 0);
	transformvec(obj->otw, tempvec, tempvec);
	fill_m_rot_v((-obj->rot[2] * M_PI) / 180.f, tempvec, temp);
	m4_mult(obj->otw, temp, obj->otw);
	fill_m_transform(temp, obj->org);
	m4_mult(obj->otw, temp, obj->otw);
	m4_invert(obj->otw, obj->wto);
}

static void	calc_cam(t_cam *cam)
{
	t_matrix	temp;

	ft_bzero(&temp, sizeof(temp));
	ft_bzero(&cam->ctw, sizeof(t_matrix));
	fill_m_rot_x(temp, (cam->rot[0] * M_PI) / 180.f);
	fill_m_rot_y(cam->ctw, (cam->rot[1] * M_PI) / 180.f);
	m4_mult(cam->ctw, temp, cam->ctw);
	FILLVEC(cam->dir, 0, 0, -1, 0);
	transformvec(cam->ctw, cam->dir, cam->dir);
	fill_m_rot_v((cam->rot[2] * M_PI) / 180.f, cam->dir, temp);
	m4_mult(cam->ctw, temp, cam->ctw);
	fill_m_transform(temp, cam->org);
	m4_mult(cam->ctw, temp, cam->ctw);
	cam->rot[0] += cam->rot[0] >= 360 ? -360 : 0;
	cam->rot[0] += cam->rot[0] <= 0 ? +360 : 0;
	cam->rot[1] = ft_clamp(90, -90, cam->rot[1]);
	cam->rot[2] += cam->rot[2] >= 360 ? -360 : 0;
	cam->rot[2] += cam->rot[2] <= 0 ? +360 : 0;
	m4_invert(cam->ctw, cam->wtc);
}

void		calc_scene(t_scene *scene)
{
	t_list *cur;

	cur = scene->cam;
	while (cur)
	{
		calc_cam(cur->content);
		cur = cur->next;
	}
	cur = scene->obj;
	while (cur)
	{
		calc_obj(cur->content);
		cur = cur->next;
	}
}
